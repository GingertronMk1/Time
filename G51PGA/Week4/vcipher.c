#include <stdio.h>
#include <string.h>

void encrypt(char *text, char *pass, int n, int m, char *vs);
void decrypt(char *text, char *pass, int n, int m, char *vs);
int upcase(char *text, int length);


int main(int argc, char *argv[]) {
    /*  1.  e or d,
        2.  passphrase as single word,
        3.  the name of file containing plaintext or ciphertext
        4.  the name of an output file. */

    /*char plaintext[1024];
    char *choose = argv[1];
    char *pass = argv[2];
    char vs[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZBCDEFGHIJKLMNOPQRSTUVWXYZACDEFGHIJKLMNOPQRSTUVWXYZABDEFGHIJKLMNOPQRSTUVWXYZABCEFGHIJKLMNOPQRSTUVWXYZABCDFGHIJKLMNOPQRSTUVWXYZABCDEGHIJKLMNOPQRSTUVWXYZABCDEFHIJKLMNOPQRSTUVWXYZABCDEFGIJKLMNOPQRSTUVWXYZABCDEFGHJKLMNOPQRSTUVWXYZABCDEFGHIKLMNOPQRSTUVWXYZABCDEFGHIJLMNOPQRSTUVWXYZABCDEFGHIJKMNOPQRSTUVWXYZABCDEFGHIJKLNOPQRSTUVWXYZABCDEFGHIJKLMOPQRSTUVWXYZABCDEFGHIJKLMNPQRSTUVWXYZABCDEFGHIJKLMNOQRSTUVWXYZABCDEFGHIJKLMNOPRSTUVWXYZABCDEFGHIJKLMNOPQSTUVWXYZABCDEFGHIJKLMNOPQRTUVWXYZABCDEFGHIJKLMNOPQRSUVWXYZABCDEFGHIJKLMNOPQRSTVWXYZABCDEFGHIJKLMNOPQRSTUWXYZABCDEFGHIJKLMNOPQRSTUVXYZABCDEFGHIJKLMNOPQRSTUVWYZABCDEFGHIJKLMNOPQRSTUVWXZABCDEFGHIJKLMNOPQRSTUVWXY";

    FILE *fp;
    fp = fopen(argv[3], "r");
    fscanf(fp, "%[^\n]", plaintext);
    fclose(fp);

    int textlength = strlen(plaintext);
    int passlength = strlen(pass);
    char key[textlength];
    upcase(plaintext, textlength);
    upcase(pass, passlength); */

    printf("I don't know how to make this work\n");

    /*if(textlength > passlength){                    //if the length of the text is greater than the pass
        for(int i = 0; i < textlength; i++){
            int inc = i;
            if(inc > passlength){
                inc = inc-passlength;
            };
            key[i] = pass[inc];
        };
    } else {
        for(int i = 0; i < textlength; i++){
            key[i] = pass[i];
        }
    };

    printf("%d\n%d\n%s\n%s\n%s\n%lu\n", textlength, passlength, plaintext, pass, key, strlen(key));

    if(*choose == 'e'){
        encrypt(plaintext, pass, textlength, passlength, vs);
    } else if(*choose == 'd'){
        decrypt(plaintext, pass, textlength, passlength, vs);
    } else {
        printf("Please input e for encrypt or d for decrypt.\n");
    }; */
};

void encrypt(char *text, char *pass, int n, int m, char *vs){
    //printf("Encrypted!\n%s\n%s\n%d\n%d\n%s\n", text, pass, n, m, vs);
};

void decrypt(char *text, char *pass, int n, int m, char *vs){
    //printf("Decrypted!\n%s\n%s\n%d\n%d\n%s\n", text, pass, n, m, vs);
};

int upcase(char *text, int length){
    char lowaz[] = "abcdefghijklmnopqrstuvwxyz ";   //the alphabet, lower case
    char upaz[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";    //the alphabet, upper case
    if(length > 0){                                 //making sure there's actually text there
        for(int i = 0; i < length; i++){            //incrementing through the text
            for(int x = 0; x < 100; x++){           //incrementing through the lower case alphabet
                if(x > strlen(lowaz)){              //if we've incremented through the lowaz and found nothing,
                    break;
                } else if (text[i] == lowaz[x]){            //comparing the text to each character in the alphabet
                    text[i] = upaz[x];              //replacing lower case with upper case
                    break;
                };
            };
       };
        return *text;                               //returning 0 for success
    } else {
        return 1;                                   //returning 1 for failure
    };
};
