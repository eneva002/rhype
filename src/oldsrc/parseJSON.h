#ifndef _parseJSON_h_
#define _parseJSON_h_

#include "dist/jsoncpp.cpp"
#include <iostream>
#include <string>

struct track
{
  std::string title;
  std::string artist;
  std::string id;
  std::string key;
  std::string title;
  
};

int getTracks(const std::string &hypeHTML, Json::Value &ret)
{
  Json::Value root;   // will contains the root value after parsing.
  Json::Reader reader;

  bool parsingSuccessful = reader.parse(hypeHTML, root, false);
  if (parsingSuccessful)
  {
    ret = root.get("tracks", "null");
    return 0;
  }
  else
  {
    return -1;
  }
}


#endif

