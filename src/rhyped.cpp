#include <iostream> 
#include <vector> 
#include "Python.h"
#include <unistd.h> 
#include <stdlib.h>
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <stdio.h>
#include <errno.h>
#include <sys/un.h>
#include <algorithm>
#include <string>
#include <ctype.h>

#define SOCK_PATH "hyped_socket"

int getTracks();
void loadTracks();

using namespace std;

struct track{
  int id;
  string artist;
  string track;
  string url;
};

int main()
{

  //leave cwd the same
  //leave std in/out/err  alone
  //if(0 != daemon(1, 1)) perror("daemon");

  //for debugging purposes
  pid_t pid = getpid();
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
      if(0 != getTracks()) strcpy(response, "update failed");
      else{
        strcpy(response, "update successful");
        loadTracks();
      }
    }
    else strcpy(response, "unknown command");
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

void loadTracks(){
  return;
}
