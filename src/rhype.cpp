#include <iostream>
#include <stdio.h>
#include <vector>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
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
  if((t = recv(sock, str, 100, 0)) > 0){
    str[t] = '\0';
    cout << "rHyped$ " << str << endl;
  }
  else {
    if(t < 0) perror("recv");
    else cout << "Server closed connection"  << endl;
    exit(1);
  }
  close(sock);
  return  0;
}
