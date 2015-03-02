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
    for (size_t i = 0; i < N; i++)
    {
    A = root[i].get("A", "ASCII").asString();
    B = root[i].get("B", "ASCII").asString();
    C = root[i].get("C", "ASCII").asString();
    D = root[i].get("D", "ASCII").asString();
    //print all of them
    cout << A << " " << B << " " << C << " " << D << endl;
    }
  }
}
