#include <stdio.h>

void smallestMoney(int i);

int main() {
    smallestMoney(20);
    smallestMoney(79);
    smallestMoney(10);
    smallestMoney(42);
    smallestMoney(0);
};

void whatToReturn(int n, int v) {       //deals with pluralizing or singularizing notes/coins as appropriate
    if(n > 1 && v > 1) {                //it's all for the smallest money thing
        printf("%d £%d notes", n, v);
    } else if(n == 1 && v > 1) {
        printf("%d £%d note", n, v);
    } else if(n > 1 && v == 1) {
        printf("%d pound coins", n);
    } else if(n == 1 && v == 1) {
        printf("one pound coin");
    };
};

void smallestMoney(int i) {
    int twenties = i/20;                //integer divides by 20 to get all £20s first
    int remaining = i%20;               //calculates the remaining
    int tens = remaining/10;            //same as twenties, except for tens
    remaining = remaining%10;           //it basically repeats down to ones
    int fives = remaining/5;
    int ones = remaining%5;
    printf("£%d consists of ", i);
    if(twenties > 0) {                               //if twenties has a value, do these
        whatToReturn(twenties,20);
        if(tens > 0 && fives > 0 && ones > 0) {      //if all the rest have values
            printf(", ");
            whatToReturn(tens,10);
            printf(", ");
            whatToReturn(fives,5);
            printf(" and ");
            whatToReturn(ones,1);
            printf(".\n");
        } else if(tens > 0 && fives > 0 && ones == 0) {   //if only tens and fives have values
            printf(", ");
            whatToReturn(tens,10);
            printf(" and ");
            whatToReturn(fives,5);
            printf(".\n");
        } else if(tens > 0 && fives == 0 && ones > 0) {  //if only tens and ones have values
            printf(", ");
            whatToReturn(tens,10);
            printf(" and ");
            whatToReturn(ones,1);
            printf(".\n");
        } else if(tens == 0 && fives > 0 && ones > 0) {  //if only fives and ones have values
            printf(", ");
            whatToReturn(fives,5);
            printf(" and ");
            whatToReturn(ones,1);
            printf(".\n");
        } else if(tens > 0 && fives == 0 && ones == 0) {   //if only tens has a value
            printf(" and ");
            whatToReturn(tens,10);
            printf(".\n");
        } else if(tens == 0 && fives > 0 && ones > 0) {   //if only fives has a value
            printf(" and ");
            whatToReturn(fives,5);
            printf(".\n");
        } else if(tens == 0 && fives == 0 && ones > 0) {   //if only ones has a value
            printf(" and ");
            whatToReturn(ones,1);
            printf(".\n");
        } else {                                          //if only twenties has a value
            printf(".\n");
        };
    } else if(tens > 0) {                 //if twenties has no value but tens does, do this
        whatToReturn(tens,10);
        if(fives > 0 && ones > 0) {      //if fives and ones have values
            printf(", ");
            whatToReturn(fives,5);
            printf(" and ");
            whatToReturn(ones,1);
            printf(".\n");
        } else if(fives > 0 && ones == 0) {       //if only fives has a value
            printf("and ");
            whatToReturn(fives,5);
            printf(".\n");
        } else if(fives == 0 && ones > 0) {       //if only ones has a value
            printf("and ");
            whatToReturn(ones,1);
            printf(".\n");
        } else {
            printf(".\n");
        }
     } else if(fives > 0) {               //if neither of the other two have values but fives does, this
        whatToReturn(fives,5);
        if(ones > 0) {                   //if ones has a value
            printf("and ");
            whatToReturn(ones,1);
            printf(".\n");
        } else {                          //if ones has no value
            printf(".\n");
        }
   } else if(ones > 0) {                  //if it can only be made of quid coins
       whatToReturn(ones,1);
       printf(".\n");
   } else {
       printf("nothing.\n");
   };
};

