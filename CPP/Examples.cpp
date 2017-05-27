#include <string>
#include <iostream>

using namespace std;
/*
void foo() {
  static int count = 0;
  count++;
  printf("Value of foo count is: %d\n", count);
}

void bar() {
  int count = 0;
  count++;
  printf("Value of bar count is: %d\n", count);
}
*/

int main() {
  string s1("Test String");
  int i = 1;
  cout << "Input Number\t";
  cin >> i;
  cout << s1 << " " << i << endl;
  cerr << s1.c_str() << endl;







  return 0;
}
