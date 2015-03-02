#ifndef _retreiveURLs_h_
#define _retreiveURLs_h_
#include "curl/curl.h"
#include "json/json.h"

#include <list>
#include <string>
#include <iostream>

size_t writeHTML(char *contents, size_t size, size_t nmemb, void *storage){
  ((std::string*)storage)->append((char*)contents, size * nmemb);
  return size * nmemb;
}

std::string getHTML(std::string URL){
  CURL *curl;
  CURLcode res;
  std::string HTML;

  curl = curl_easy_init();
  if(curl){
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeHTML);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &HTML);
    res = curl_easy_perform(curl);

    if(res != CURLE_OK){
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    curl_easy_cleanup(curl);
  }

  return HTML;
}

#endif
