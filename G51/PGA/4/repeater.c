#include <stdio.h>
#include <string.h>

void repeater(char *textOne, char *textTwo);

int main(int argc, char *argv[]){
    repeater("When I was a boy", "Lynne");
};

void repeater(char *textOne, char *textTwo){
    int textOneLength = strlen(textOne);
    int textTwoLength = strlen(textTwo);
    printf("%s, %s\n", textOne, textTwo);

    if(textOneLength > textTwoLength){
        char textTwoLonger[textOneLength];
        for(int i = 0; i < textOneLength; i++){
            int looper = i;
            if((looper / textTwoLength) > 0){
                looper = looper - ((textTwoLength)*(looper/textTwoLength));
            };
            textTwoLonger[i] = textTwo[looper];
        };
    int textTwoLongerLength = strlen(textTwoLonger);
    printf("%s, %d, %d\n", textTwoLonger, textTwoLongerLength, textOneLength);
    };
};
