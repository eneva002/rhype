#ifndef _getHTML_h_
#define _getHTML_h_
#include "curl/curl.h"

#include <string>
#include <iostream>

size_t writeHTML(char *contents, size_t size, size_t nmemb, void *storage){
  ((std::string*)storage)->append((char*)contents, size * nmemb);
  return size * nmemb;
}

int getHTML(std::string URL, std::string *HTML){
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl){
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeHTML);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, HTML);
    res = curl_easy_perform(curl);

    if(res != CURLE_OK){
      std::cerr << "curl_easy_perform() failed: " <<  curl_easy_strerror(res) 
                << std::endl;
      curl_easy_cleanup(curl);
      return -1;
    }

    curl_easy_cleanup(curl);
  }

  return 0;
}

int parseHTML(std::string *HTML){
  size_t start = HTML->find("id=\"displayList-data\"");
  if(start == std::string::npos) return -1;

  size_t end = HTML->find("</script>", start);
  if(end == std::string::npos) return -1;
  
  *HTML = HTML->substr(start, end-start);

  start = HTML->find(">");
  if(start == std::string::npos) return -1;

  *HTML = HTML->substr(start+1, end-start-1);

  return 0;
}

#endif
