#include <cstdio> /* for printf */
int main( int argc, char* argv[] ) {
  int x = 1;
  do {
    printf("X is %d\n", ++x);
  } while(x < 10);
  return 0;
}
