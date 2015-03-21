#include <iostream>
#include <stdio.h>
#include <vector>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <signal.h>
#include <fstream>
#include <sys/types.h>
#include <sys/un.h>
#include <stdlib.h>

#define SOCK_PATH "hyped_socket"

using namespace std;

int main(int argc, char**argv)
{
  if(argc != 2){
    cout << "Correct usage: `rhype <command>`" << endl;
    exit(1);
  }

  char *home = getenv("HOME");
  strcat(home, "/rhype");

  if(-1 == chdir(home))
  {
    perror("couldn't find home");
    exit(1);
  }

  ifstream fin("pid");
  if(!fin.is_open()) perror("PID FILE NOT FOUND");
  string crhypedID;
  getline(fin, crhypedID);
  fin.close();
  int rhypedID = atoi(crhypedID.c_str());

  if(!strcmp(argv[1], "stop"))
  {
    kill(rhypedID, SIGQUIT);
    return 0;
  }
  else if(!strcmp(argv[1], "pause"))
  {
    kill(rhypedID, SIGTSTP);
    return 0;
  }
  else if(!strcmp(argv[1], "resume"))
  {
    kill(rhypedID, SIGCONT);
    return 0;
  }
  else if(!strcmp(argv[1], "skip"))
  {
    kill(rhypedID, SIGINT);
    return 0;
  }
  else if(!strcmp(argv[1], "help"))
  {
    cout << "`update` fetches the latest playlist from hypem" << endl;
    cout << "`list` displays the current playlist" << endl;
    cout << "`play` plays all songs in the playlist from the beginning" <<  endl;
    cout << "`stop` stops the player" << endl;
    cout << "`skip` skips the current song" <<endl;
    cout << "`pause` pauses the player"  << endl;
    cout << "`resume` resumes playing" << endl;
    cout << "`help` does this "  << endl;
    return 0;
  }
  else if(strcmp(argv[1], "update") && strcmp(argv[1], "play") && strcmp(argv[1], "list")) {
    cout << "invalid command, use `rhype help` for reference" << endl;
    exit(1);
  }
      
  struct sockaddr_un remote;
  
  int sock;
  if((sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
    perror("socket");
    exit(1);
  }

  remote.sun_family = AF_UNIX;
  strcpy(remote.sun_path, SOCK_PATH);
  int len = strlen(remote.sun_path) + sizeof(remote.sun_family);
  if(connect(sock, (struct sockaddr*)&remote, len) == -1){
    perror("connect");
    exit(1);
  }

  if(send(sock, argv[1], strlen(argv[1]), 0) ==  -1){
    perror("send");
    exit(1);
  }

  int t;
  char str[100];
  while((t = recv(sock, str, 100, 0)) > 0){
    str[t] = '\0';
    cout << str;
    if(t < 0){
      perror("recv");
      break;
    }
  }
  close(sock);
  return  0;
}
