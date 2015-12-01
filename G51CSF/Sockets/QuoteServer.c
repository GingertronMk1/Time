//
//  QuoteServer
//
//  Created by <insert name>
//  Username: <inser username>
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/socket.h>

#define kQUOTEPORT      1717
#define kMULTIQUOTEPORT 1818
#define QUOTELEN 256

struct quote *createQuote(char line[QUOTELEN]);
struct quote *addQuote(struct quote *new, struct quote *head);
struct quote *readQuotes(char *filename);
int countList(struct quote *head);
char[QUOTELEN] randomQuote(int n, struct quote *head);



struct quote {          //Defining the struct type 'quote'
    char line[QUOTELEN];
    struct quote *next;
}

struct quote *createQuote(char line[QUOTELEN]){                 //Creates a new struct quote
    struct quote *a = (struct quote *)malloc(sizeof(struct quote));
    if(a != NULL){
        a->line = line;
        a->next = NULL;
    }
}

struct quote *addQuote(struct quote *new, struct quote *head){      //Adds a new quote to a linked list
    if(new != NULL){
        new->next = head;
        return new;
    } else {
        return head;
    }
}

struct quote *readQuotes(char *filename){       //Reads a text file of quotes into a linked list
    char quote[QUOTELEN];
    char line
    file quoteFile = fopen(file_name, "r");
    struct quote *tmp = malloc(sizeof(struct quote));
    if(quoteFile != NULL){
        while(fscanf(quoteFile, "%s\n", quote)){
            struct quote *new = createQuote(quote);
            tmp = addQuote(new,tmp);
            tmp = new;
        };
        fclose(quoteFile);
        return tmp;
    } else {
        fclose(quoteFile);
        printf("File Error\n");
        exit(1);
    }
}

int countList(struct quote *head){          //Counts the number of elements in a linked list of quotes
    if(head != NULL){
        struct quote *q = head;
        int count = 0;
        while(q != NULL){
            count++;
            q = q->next;
        }
    } else {
        printf("List Error\n");
    }
}

char[QUOTELEN] randomQuote(int n, struct quote *head){
    double random = (double)rand()/(double)RAND_MAX;
    int quoteNumber = n*random;
    if(head != NULL){
        struct quote *q = head;
        int count = 0;
        for(int count = 0; count < quoteNumber; count++){
            q = q->next;
        }
        return q->quote;
    } else {
        printf("List Error in generating random quote\n");
    }
}

int main(int argc, const char * argv[])
{
    struct quote quotes = readQuotes("Quotes.txt");
    int quoteCount = countList(quotes);
    printf("%s\n", randomQuote(quoteCount, quotes);
    return 0;
}
