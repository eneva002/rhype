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

int main()
{
  struct sockaddr_un remote;
  char str[100];
  
  int sock;
  if((sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
    perror("socket");
    exit(1);
  }

  cout << "Attempting connection ..." << endl;

  remote.sun_family = AF_UNIX;
  strcpy(remote.sun_path, SOCK_PATH);
  int len = strlen(remote.sun_path) + sizeof(remote.sun_family);
  if(connect(sock, (struct sockaddr*)&remote, len) == -1){
    perror("connect");
    exit(1);
  }

  cout << "Connected." << endl;

  int t;
  while(1)
  {
    cout << ">> ";
    fgets(str, 100, stdin);

    if(send(sock, str, strlen(str), 0) ==  -1){
      perror("send");
      exit(1);
    }

    if((t = recv(sock, str, 100, 0)) > 0){
      str[t] = '\0';
      cout << "rHyped$ " << str;
    }
    else {
      if(t < 0) perror("recv");
      else cout << "Server closed connection"  << endl;
      exit(1);
    }
  }
  close(sock);
  return  0;
}
