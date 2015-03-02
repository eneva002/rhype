#include "dist/jsoncpp.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main(){
  Json::Value root;   // will contains the root value after parsing.
  Json::Reader reader;
  string data;
  ifstream fin("test.json");
  stringstream temp;
  temp << fin.rdbuf();
  data = temp.str();
  cout << data;

  bool parsingSuccessful = reader.parse(data, root, false);
  int N = root.size();
  string A, B, C, D;
  if (parsingSuccessful)
  {
    cout << root << endl;
    Json::Value test = root.get("test", "null");
    cout << "++++++++++++++++++" << endl;
    cout << test << endl;
    Json::Value test1 = test[1].get("A", "null");
    cout << "++++++++++++++++++" << endl;
    cout << test1 << endl;
  }

}
