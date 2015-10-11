#include <stdio.h>

void printPSP(int p);

int main() {
    printPSP(11);
    printPSP(13);
    printPSP(42);
    printPSP(100);
    printPSP(241);
};

void printPSP(int p){
    int pounds = p/240;
    int pennies = p-(pounds*240);
    int shillings = pennies/12;
    pennies = pennies - (shillings*12);
    printf("%d pennies is %d pounds, %d shillings and %d pennies\n", p, pounds, shillings, pennies);
};

