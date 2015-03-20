#include <sys/socket.h> 
#include <sys/types.h> 
#include <sys/wait.h>
#include <sys/stat.h>
#include <algorithm>
#include <iostream> 
#include <sys/un.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <fstream>
#include <string>
#include <vector> 

#include "curl/curl.h"

#define SOCK_PATH "hyped_socket"

int getTracks();
int loadTracks();
int dlSong(int);

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

int main()
{
  string nuurl = "http://api.soundcloud.com/tracks/196448361/stream?consumer_key=nH8p0jYOkoVEZgJukRlG6w";
  track newtrack;
  tracks.push_back(newtrack);
  tracks[0].url = nuurl;

  int pid = fork();
  if(pid == 0){
    if(dlSong(0) < 0) perror("fail");
  }
  else if(pid > 0){
    cout << "THIS IS A TEST +++++++++++++++++++++++++++++++++" << endl;
    wait(0);
  }
  else perror("FUCK");
  

  return  0;
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
  char cmd[500] = "wget -O tmp.mp3 "; 
  strcat(cmd, tracks.at(trackno).url.c_str());
  strcat(cmd, " &&  mpg123 tmp.mp3");
  system(cmd);
  
  return 0;
}
