#include <cstdio>

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

int main() {
  int i;
  for(i = 0; i < 5; i++)
    foo();
  for(i = 0; i < 5; i++)
    bar();
  return 0;
}
