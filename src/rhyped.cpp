#include "hypedExec.h"

#define SOCK_PATH "hyped_socket"

using namespace std;

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
    
    done = 0;
    //ignore any commands longer than 100 characters
    do{
      n  = recv(sock2, str, 100, 0);
      if(n <= 0) {
        if(n < 0) perror("recv");
        done = 1;
      }
      if(!done)
        if(hypedExec(str) != 0){
          done = 1;
          perror("hypedExec");
        } 
    } while(!done);
    close(sock2);
  }
  return  0;
}
