#include "getHTML.h"
//int getHTML(std::string URL, std::string *HTML);
//int parseHTML(std::string *HTML);

#include "parseJSON.h"
//int getTracks(const string &hypeJSON, Json::Value &ret)

using namespace std;

int main()
{
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

  //get tracklist
  Json::Value tracks;
  ret = getTracks(hypeHTML, tracks);
  if(ret != 0) std::cout << "JSON parsing failed" << std::endl;

  std::cout << tracks;

  return ret;

}
