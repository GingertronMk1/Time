#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  char operator = *argv[1];
  int result, c, r;
  int cols = atoi(argv[2]);
  int rows = atoi(argv[3]);
  printf("\t%c\t|", operator);
  for (r = 1; r <= rows; r++) {   // Printing the header row
    printf("\t%d", r);
  }
  printf("\n----------------+");
  for (r = 1; r <= rows; r++) {
    printf("--------");
  }
  printf ("----\n");
  for (c = 1; c <= cols; c++) {
    printf("\t%d\t|", c);   // Printing the header column
    for (r = 1; r <= rows; r++) {
      switch(argv[1][0]) {    // Choosing the right operation
        case '+':result=c+r; break;
        case '-':result=c-r; break;
        case '*':result=c*r; break;
        case '/':result=c/r; break;
        case '%':result=c%r; break;
        case '&':result=c&r; break;
        case '|':result=c|r; break;
        case '^':result=c^r; break;
        default: printf("\n\nPLEASE USE ONE OF `+, -, '*', /, %%, '&', '|', ^`.\n\n"); return 0;
      }
      printf("\t%d", result); // Returning the correct number
    }
    printf("\t\n");
  }
  return 0;
}
