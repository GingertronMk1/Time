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
#define BUFSIZE 512
#define WAITING 0
#define SENTQUOTE 1
#define ANOTHER 3
#define NO 4

struct quote *createQuote(char line[BUFSIZE]);                 //Creates a new struct quote
struct quote *addQuote(struct quote *new, struct quote *head);      //Adds a new quote to a linked list
struct quote *readQuotes(char *filename);       //Reads a text file of quotes into a linked list
int countList(struct quote *head);
struct quote quoteN(int n, struct quote *head);
void answers(char filename[BUFSIZE], int count);
void printQuote(char filename[BUFSIZE], int count);

struct quote {          //Defining the struct type 'quote'
    char line[BUFSIZE];
    struct quote *next;
};

int main(int argc, const char * argv[]){
    char filename[BUFSIZE];
    strcpy(filename, argv[1]);
    printQuote(filename, 0);
    return 0;
}

/*
 *
 *
 *   Quote file reading stuff
 *
 *
 */

struct quote *createQuote(char line[BUFSIZE]){                 //Creates a new struct quote
    struct quote *a = (struct quote *)malloc(sizeof(struct quote));
    if(a != NULL){
        strcpy(a->line, line);
        a->next = NULL;
        return a;
    } else {
        return NULL;
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
    char quote[BUFSIZE];
    char line;
    FILE *quoteFile = fopen(filename, "r");
    struct quote *tmp = malloc(sizeof(struct quote));
    if(quoteFile != NULL){
        while(fgets(quote,BUFSIZE,quoteFile) != NULL){
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
        return count-1;
    } else {
        printf("List Error\n");
        return 0;
    }
}

struct quote quoteN(int n, struct quote *head){
    if(head != NULL){
        struct quote *q = head;
        int count = 0;
        for(int count = 0; count < n; count++){
            q = q->next;
        }
        return *q;
    } else {
        printf("List Error in generating random quote\n");
        return *head;
    }
}

void answers(char filename[BUFSIZE], int count){
    char answer[BUFSIZE];
    scanf("%s", answer);
    char another[] = "ANOTHER";
    char close[] = "CLOSE";
    if(strcmp(answer,another) == 0){
        printf("\n");
        printQuote(filename, ++count);
    } else if(strcmp(answer,close) == 0){
        printf("Bye!\n");
    } else {
        printf("Error, try again!\n");
        answers(filename, count);
    }
}

void printQuote(char filename[BUFSIZE], int count){
    struct quote *quotes = readQuotes(filename);
    int quoteCount = countList(quotes);
    if(quoteCount > count){
        struct quote nthQuote = quoteN(count,quotes);
        printf("%s\n", nthQuote.line);
        printf("Would you like ANOTHER or should I CLOSE?\n");
        answers(filename, count);
    } else {
        count = 0;
        printQuote(filename, count);
    }
}

/*
*
*
*       NETWORK STUFF STARTS HERE
*
*
*/
