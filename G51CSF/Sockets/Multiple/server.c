//
//  QuoteServer
//
//  Created by Jack Ellis
//  Username: psyje5
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
#include <math.h>
#include <time.h>

#define kQUOTEPORT      1717
#define kMULTIQUOTEPORT 1818
#define NETBUFSIZE 12
#define WAITING 0
#define SENTKNOCKKNOCK 1
#define SENTCLUE 2
#define ANOTHER 3
#define BYE 4
#define BUFSIZE 512

struct quote {
    char line[BUFSIZE];
    struct quote *next;
};

void ServerConnection(int fd, char *filename);
struct quote *createQuote(char line[BUFSIZE]);
struct quote *readQuotesFromFile(char *filename);
int countLinkedList(struct quote *head);
struct quote *randomQuote(int listLength, struct quote *head);
struct quote randomQuoteFromFile(char *filename);
void printAllQuotes(struct quote *head);

int main(int argc, const char * argv[]){
    int serverSocket, clientConnection;
    struct sockaddr_in server;
    struct sockaddr_in client;
    unsigned int alen;

    printf("Listening for connections on port %d\n", kQUOTEPORT);
    
    serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(kQUOTEPORT);
    server.sin_addr.s_addr = INADDR_ANY;
    char quoteFile[BUFSIZE];
    printf("Scanning quote file name\n");
    if(argc == 2){
        sscanf(argv[1], "%s", quoteFile);
    } else {
        printf("No quote file given: falling back to default: Quotes.txt\n");
        strcpy(quoteFile, "Quotes.txt");
    };
    printf("%s\n", quoteFile);
    
    /* bind socket */
    if((bind(serverSocket, (struct sockaddr*)&server, sizeof(server)) < 0))
    {
        printf("bind() failed -- %d\n", errno);
        return 1; /* Error */
    }
    
    /* Mark the connection as listening */
    if(listen(serverSocket, 15) < 0)
    {
        fprintf(stderr, "Failed to listen()\n");
        return 2;
    }
    
    while(1)
    {
        alen = sizeof(client);
        clientConnection = accept(serverSocket, (struct sockaddr*)&client, &alen);
        if(clientConnection < 0)
        {
            fprintf(stderr, "Accept failed -- %d %d\n", clientConnection, errno);
            return 3;
        }
        
        printf("Connection from %x port %d...\n", ntohl(client.sin_addr.s_addr), ntohs(client.sin_port));
        
        /* Handle connection */
        ServerConnection(clientConnection, quoteFile);
        
        close(clientConnection);
    }
    
    return 0;
}

/*
   *
   *
   *        QUOTE READING/PARSING CODE
   *
   *
   */

struct quote *createQuote(char line[BUFSIZE]){
    struct quote *a = (struct quote *)malloc(sizeof(struct quote));
    if(a != NULL){
        strcpy(a->line, line);
        a->next = NULL;
        return a;
    } else {
        return NULL;
    }
}

struct quote *readQuotesFromFile(char *filename){
    char line[BUFSIZE];
    FILE *quoteFile = fopen(filename, "r");
    struct quote *tmp = malloc(sizeof(struct quote));
    if(quoteFile != NULL){
        while(fgets(line,BUFSIZE,quoteFile) != NULL){
            struct quote *new = createQuote(line);
            new->next = tmp;
            tmp = new;
        };
        fclose(quoteFile);
        return tmp;
    } else {
        fclose(quoteFile);
        printf("Error reading file\n");
        return NULL;
    }
}

int countLinkedList(struct quote *head){
    if(head != NULL){
        struct quote *q = head;
        int n = 0;
        while(q != NULL){
            n++;
            q = q->next;
        };
        return n-1;
    } else {
        printf("Error: linked list is NULL\n");
        return 0;
    }
}

struct quote *randomQuote(int listLength, struct quote *head){
    if(head != NULL){
        struct quote *q = head;
        srand(time(NULL));
        int randomNumber = fabs(cos(rand())) * listLength;
        for(int i = 0; i < randomNumber; i++){
            q = q->next;
        }
        return q;
    } else {
        printf("Error selecting random quote: list empty\n");
        return NULL;
    }
}

struct quote randomQuoteFromFile(char *filename){
    struct quote *list = readQuotesFromFile(filename);
    int numberOfQuotes = countLinkedList(list);
    struct quote *random = randomQuote(numberOfQuotes, list);
    return *random;
}

void printAllQuotes(struct quote *head){
    struct quote *q = head;
    int counter = 0;
    while(q != NULL){
        printf("%d:\t%s\n", counter++, q->line);
        q = q->next;
    }
}

/*
   *
   *
   *        NETWORK CODE
   *
   *
   *
   */

void ServerConnection(int fd, char *filename){
    char outBuffer[BUFSIZE];
    char inputBuffer[BUFSIZE];
    ssize_t n;
    
    sprintf(outBuffer, "Today's Quote:\t%s\r\n", randomQuoteFromFile(filename).line);
    write(fd, outBuffer, strlen(outBuffer));
}
