#include <stdio.h>

void moneyCalc(int x);
void printSumPSP(
     int xPounds, int xShillings, int xPennies,
     int yPounds, int yShillings, int yPennies);

int main(){
    printSumPSP(1,4,3,2,17,8);
    printSumPSP(1,5,9,0,1,11);
    printSumPSP(1,19,11,0,0,1);

};

void printSumPSP(
    int xPounds, int xShillings, int xPennies,
    int yPounds, int yShillings, int yPennies){
    int xnewPence = (xPounds*240) + (xShillings*12) + xPennies; //converts from PSP to pennies
    int ynewPence = (yPounds*240) + (yShillings*12) + yPennies;
    int newPrice = xnewPence + ynewPence; //adds penny values together
    int pounds = newPrice/240;
    int pennies = newPrice-(pounds*240);
    int shillings = pennies/12;
    pennies = pennies - (shillings*12); //converts back to PSP from pennies
    printf("Adding %d pounds, %d shillings, and %d pennies,\nand %d pounds, %d shillings and %d pennies\ngives %d pounds, %d shillings, and %d pennies.\n\n", xPounds, xShillings, xPennies, yPounds, yShillings, yPennies, pounds, shillings, pennies);
}
