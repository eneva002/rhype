#include "retrieveURLs.h"

//std::string getHTML(std::string URL);

int main(){
  std::string hypeURL = "http://hypem.com/popular";
  std::string hypeHTML = getHTML(hypeURL);

  std::cout << hypeHTML << std::endl;

}
