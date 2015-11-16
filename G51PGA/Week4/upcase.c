#include <stdio.h>
#include <string.h>

int upcase(char *text, int length);

int main() {
    char text[80];
    printf("Please enter your text below:\n");
    scanf("%80[^\n]", text);
    int length = strlen(text);
    upcase(text, length);
};

int upcase(char *text, int length){
    char lowaz[] = "abcdefghijklmnopqrstuvwxyz ";   //the alphabet, lower case
    char upaz[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";    //the alphabet, upper case
    if(length > 0){                                 //making sure there's actually text there
        for(int i = 0; i < length; i++){            //incrementing through the text
            for(int x = 0; x < 100; x++){           //incrementing through the lower case alphabet
                if(x > strlen(lowaz)){              //if we've incremented through the lowaz and found nothing,
                    printf("Error:  Non-English character\n");  //there's a non-english character, so fail condition
                    return 1;
                } else if (text[i] == lowaz[x] || text[i] == upaz[x]){            //comparing the text to each character in the alphabet
                    text[i] = upaz[x];              //replacing lower case with upper case
                    break;
                };
            };
       };
        printf("%s\n",text);                        //printing the result
        return *text;                               //returning 0 for success
    } else {
        return 1;                                   //returning 1 for failure
    };
};
