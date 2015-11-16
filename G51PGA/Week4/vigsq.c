#include <stdio.h>
#include <string.h>

void vigsq(char *vs);

int main() {
    vigsq("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
};

void vigsq(char *vs){
    int length = strlen(vs);                                //separating the length of the string
    char vigsquare[26*26];                                  //correctly sized array to hold result
    for(int row = 0; row < length; row++){                  //making all the rows
        for(int column = 0; column < length; column++){     //making all the columns
            int letter = column + row;                      //creating an offset
            if(letter >= length){
                letter = letter - length;                   //making it 'wrap around'
            };
            printf("%c", vs[letter]);                       //printing charwise
            vigsquare[(row * 26) + column] = vs[letter];    //populating vigsquare array
        };
        printf("\n");                                       //new line statement at end of line
    };
};
