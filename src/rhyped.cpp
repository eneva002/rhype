#include "getHTML.h"
//int getHTML(std::string URL, std::string *HTML);
//int parseHTML(std::string *HTML);

#include "parseJSON.h"


int main(){
  //error check value
  int ret;

  //page to search
  std::string hypeURL = "http://hypem.com/popular";

  //string storing HTML data
  std::string hypeHTML; 

  //retreive HTML data from URL
  ret = getHTML(hypeURL, &hypeHTML);
  if(ret != 0) std::cout << "HTML retreival failed" << std::endl;

  //parse HTML for JSON content
  ret = parseHTML(&hypeHTML);
  if(ret != 0) std::cout << "HTML parsing failed" << std::endl;

  std::cout << hypeHTML << std::endl;
  //determine starting location for parsing
  //std::cout << start << std::endl;
  //std::cout << hypeHTML.substr(start);
  std::cout << std::endl;
  return ret;

}
