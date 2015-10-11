#include <stdio.h>

double calcE(double m, double c);
void printE(double m, double c);

int main() {
    float c = 2.99792458;
    printE(1, c);
    printE(3.142, c);
    printE(10, c);
    printE(42, c);
};

double calcE(double m, double c) {
    return(m*c*c*0.1);
};

void printE(double m, double c) {
    printf("The energy available from an object of mass %.2f kg is %.2f PJ.\n", m, calcE(m, c));
};
