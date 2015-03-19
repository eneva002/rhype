//NOTE: the cwd should contain the python files for the python embedding to work
#include "getTracks.h"

#include <iostream> 
#include <vector> 
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

int hypedExec(int sockfd, char *str, int size)
  //int gettracks();
{
  std::string cmd = str;
  if(cmd == "update");

  std::cout << "cmd: " << cmd << std::endl << std::flush;

  




  char resp[] = "CMD RECEIVED";
  send(sockfd, resp, strlen(resp), 0);
  return 0;
}
