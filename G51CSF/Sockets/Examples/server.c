//
//  main.c
//  KnockKnockServer
//
//  Created by Steven Bagley on 12/11/2015.
//  Copyright © 2015 Steven Bagley. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>

#define kBufSize 12
#define WAITING 0
#define SENTKNOCKKNOCK 1
#define SENTCLUE 2
#define ANOTHER 3
#define BYE 4

char *clues[] = { "Turnip", "Little Old Lady", "Atch", "Who", "Who" };
char *answers[] = { "Turnip the heat, it's cold in here!",
    "I didn't know you could yodel!",
    "Bless you!",
    "Is there an owl in here?",
    "Is there an echo in here?" };
#define kNUMCLUES 5

void ServerConnection(int fd);

int main(int argc, const char * argv[])
{
    int serverSocket, clientConnection;
    struct sockaddr_in server;
    struct sockaddr_in client;
    unsigned int alen;

    printf("Listening for connections on port 4444\n");
    
    serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(4444);
    server.sin_addr.s_addr = INADDR_ANY;
    
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
        
        printf("Conenction from %x port %d...\n", ntohl(client.sin_addr.s_addr), ntohs(client.sin_port));
        
        /* Handle connection */
        ServerConnection(clientConnection);
        
        close(clientConnection);
    }
    
    return 0;
}

void ServerConnection(int fd)
{
    char outBuffer[512];
    char inputBuffer[512];
    int state = WAITING;
    int joke = 0;
    ssize_t n;
    
    sprintf(outBuffer, "Knock! Knock!\r\n");
    write(fd, outBuffer, strlen(outBuffer));
    state = SENTKNOCKKNOCK;

    while(state != BYE)
    {
        /* read input */
        n = read(fd, inputBuffer, 510);
        if(n <= 0)
        {
            fprintf(stderr, "read error\n");
            return;
        }
        inputBuffer[n] = 0;
        
        if(state == SENTKNOCKKNOCK)
        {
            if(0 == strcasecmp(inputBuffer, "Who's there?\r\n"))
            {
                sprintf(outBuffer, "%s\r\n", clues[joke]);
                state = SENTCLUE;
            }
            else
            {
                sprintf(outBuffer, "You're supposed to say \"Who's there?\"! Try again. Knock! Knock!\r\n");
            }
            
        }
        else if(state == SENTCLUE)
        {
            /* Expected response */
            sprintf(outBuffer, "%s who?\r\n", clues[joke]);
            
            if(0 == strcasecmp(inputBuffer, outBuffer))
            {
                sprintf(outBuffer, "%s Want another? (y/n)\r\n", answers[joke]);
                state = ANOTHER;
            }
            else
            {
                sprintf(outBuffer, "You're supposed to say \"%s who?\"! Try again. Knock! Knock!\r\n", clues[joke]);
            }

        }
        else if(state == ANOTHER)
        {
            if(inputBuffer[0] == 'y' || inputBuffer[0] == 'Y')
            {
                joke = (joke + 1) % kNUMCLUES;
                sprintf(outBuffer, "Knock! Knock!\r\n");
                state = SENTKNOCKKNOCK;
            }
            else
            {
                sprintf(outBuffer, "Bye.\r\n");
                state = BYE;
            }
            
        }
    
        /* Write the output */
        write(fd, outBuffer, strlen(outBuffer));
    }
    
    
}



