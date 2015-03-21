#include <sys/socket.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <sys/wait.h>
#include <algorithm>
#include <iostream> 
#include <sys/un.h>
#include <signal.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#include <fstream>
#include <string>
#include <vector> 

#include "curl/curl.h"
#include "Python.h"

#define SOCK_PATH "hyped_socket"

int getTracks();
int loadTracks();
int dlSong(int);
void  parse(char *, char **);

using namespace std;

struct track{
  int id;
  string artist;
  string trackname;
  string url;
};

//global vector to store tracks
vector<track> tracks;
//global int to store current track
int currentsong = -1;
pid_t currentpid = -1;
int g_i;

void sig_handler(int signum)
{
  if(signum == SIGQUIT) g_i = tracks.size();
  if(currentpid > 0)
  {
    kill(currentpid, signum);
  }
}

int main()
{
  //leave cwd the same because i'm changing it anyways
  //ignore cin/out/err
  if(0 != daemon(1, 0)) perror("daemon");

  char *home = getenv("HOME");
  strcat(home, "/rhype");

  if(-1 == chdir(home))
  {
    perror("couldn't find home");
    exit(1);
  }

  ofstream fout("pid");
  //for debugging purposes
  pid_t pid = getpid();
  fout << pid << endl;
  fout.close();
  //cout << endl;
  cout << "session PID: " << pid << endl;
  cout << "cwd: " << get_current_dir_name() << endl;

  struct sockaddr_un local, remote;
  char str[100];
  int sock;
  if((sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
    perror("socket");
    exit(1);
  }

  local.sun_family = AF_UNIX;
  strcpy(local.sun_path, SOCK_PATH);
  unlink(local.sun_path);
  int len = strlen(local.sun_path) + sizeof(local.sun_family);
  if(bind(sock, (struct sockaddr*)&local, len) == -1){
    perror("bind");
    exit(1);
  }

  if(listen(sock,5) ==  -1){
    perror("listen");
    exit(1);
  }

  char *cmdv[3];
  cmdv[0] = strdup("mpg123");
  cmdv[1] = strdup("tmp.mp3");
  cmdv[2] = NULL; 

  cout << cmdv[0] << " " << cmdv[1] << endl << flush;

  while(1)
  {
    int done, n, sock2;
    cout << "Waiting for a connection ..."  << endl;
    socklen_t t  = sizeof(remote);
    if((sock2 = accept(sock, (struct sockaddr*)&remote,  &t)) == -1){
      perror("accept");
      exit(1);
    }
    cout << "Connected." << endl;
    n  = recv(sock2, str, 100, 0);
    if(n <= 0) {
      if(n < 0) perror("recv");
    }
    char response[100];

    //COMMANDS AND STUFF BEGIN HERE
    if(0 == strcmp(str, "update")){
      if(0 != getTracks()) strcpy(response, "update failed\n");
      else{
        if(0 != loadTracks()) strcpy(response, "load failed\n");
        else strcpy(response, "update successful!\n");
      }
    }
    else if(0 == strcmp(str, "exit")){
      exit(0);
    }
    else if(0 == strcmp(str, "list")){
      if(!tracks.empty()){
        for(int i = 0; i < tracks.size(); ++i){
          if(i == currentsong) sprintf(response, "-%d", i+1);
          else sprintf(response, "%d", i+1);
          strcat(response, ": ");
          strcat(response, tracks.at(i).artist.c_str());
          strcat(response, " - ");
          strcat(response, tracks.at(i).trackname.c_str());
          strcat(response, "\n");
          if(-1 == send(sock2, response, strlen(response), 0)){
            perror("send");
          }
          memset(response, 0, 100);
        }
      }
      else strcpy(response, "tracklist unavailable, please update\n");
    }
    else if(0 == strcmp(str, "play")){
      for(g_i = 0; g_i < tracks.size(); ++g_i)
      {
        dlSong(g_i);
        currentpid = fork(); 
        if(currentpid < 0) perror("fork");
        else if(currentpid == 0)
        {
          signal(SIGINT, SIG_DFL);
          signal(SIGQUIT, SIG_DFL);
          signal(SIGTSTP, SIG_DFL);
          signal(SIGCONT, SIG_DFL);
          close(sock2);
          execvp(cmdv[0], cmdv);
        }
        else 
        {
          signal(SIGINT, sig_handler);
          signal(SIGQUIT, sig_handler);
          signal(SIGTSTP, sig_handler);
          signal(SIGCONT, sig_handler);
          strcpy(response, "playing all songs\n");
          if(-1 == send(sock2, response, strlen(response), 0)) perror("send");
          close(sock2);
          if(-1 == wait(0)) perror("wait");
          currentpid = -1;
          continue;
        }
      }
    }
    else strcpy(response, "unrecognized command\n");
    memset(str, 0, 100);
    if(-1 == send(sock2, response, strlen(response), 0)) perror("send");
    close(sock2);
  }
  return  0;
}

int getTracks()
{
  char cName[] = "hyped.py";
  char flags[] = "r";
  Py_Initialize();
  FILE* file = fopen(cName, flags);
  if(file == NULL){
    perror("fopen");
    return 1;
  }
  if(0 != PyRun_SimpleFile(file, cName)) perror("PyRun_SimpleFile");
  Py_Finalize();
  if(0 != fclose(file)) perror("fclose");
  return 0;
}

int loadTracks(){
  tracks.clear();
  ifstream fin("track.list");
  if(!fin.is_open()){
    return -1;
  }
  int i = 0;
  string loader;
  track newtrack;
  while(getline(fin, loader)){
    tracks.push_back(newtrack);
    tracks.at(i).id = i;
    getline(fin, tracks.at(i).trackname);
    getline(fin, tracks.at(i).artist);
    getline(fin, tracks.at(i).url);
    ++i;
  }
  fin.close();
  return 0;
}

//return the PID of child process for signal stuff
int dlSong(int trackno)
{
  if(trackno != currentsong){
    char cmd[500] = "wget -O tmp.mp3 ";  
    strcat(cmd, tracks.at(trackno).url.c_str()); 
    system(cmd);
  }
  return 0;
}

void parse(char *line, char **argv)
{
  while (*line != '\0') {       /* if not the end of line ....... */ 
    while (*line == ' ' || *line == '\t' || *line == '\n')
      *line++ = '\0';     /* replace white spaces with 0    */
    *argv++ = line;          /* save the argument position     */
    while (*line != '\0' && *line != ' ' && 
      *line != '\t' && *line != '\n') 
    line++;             /* skip the argument until ...    */
  }
  *argv = '\0';                 /* mark the end of argument list  */
}
