#include "hypedExec.h"
#include <string.h>
#include <iostream>

using namespace std;

int main()
{
  char s1[] = "  helllo\n";
  char s2[] = "  hello world\n";
  char s3[] = "    a\n";
  char s4[] = " 1\n";
  char s5[] = "\0";
  char s6[] = "\n";
  char s7[] = "\t";

  cout << s1 << endl;
  cout << s2 << endl;
  cout << s3 << endl;
  cout << s4 << endl;
  cout << s5 << endl;
  cout << strip(s1) << endl;
  cout << strip(s2) << endl;
  cout << strip(s3) << endl;
  cout << strip(s4) << endl;
  cout << strip(s5) << endl;
  cout << strip(s6) << endl;
  cout << strip(s7) << endl;
}
