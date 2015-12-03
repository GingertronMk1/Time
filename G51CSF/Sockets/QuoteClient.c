//
//  QuoteClient
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
#define BUFSIZE         12

int main(int argc, const char * argv[])
{
    char buf[BUFSIZE+1];
    char line[128];
    ssize_t n;
    int i;

    int sockFD;
    int port;
    struct sockaddr_in sad;
    struct hostent *ptrh;

    sockFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    memset(&sad, 0, sizeof(sad));

    ptrh = gethostbyname(argv[1]);
    sad.sin_port = htons(port);
    connect(sockFD, (struct sockaddr*)&sad, sizeof(sad));

    do{
        n = read(sockFD, buf, BUFSIZE);
        buf[n] = '\0';
        if(n <= 0){
            break;
        }
        for(i = 0; i < n; i++){
            if(buf[i] == 10){
                break;
            }
        }
        printf("%s\n", buf);
        fgets(line, 120, stdin);
        line[strlen(line)-1] = 0;
        strcat(line, "\r\n");
        write(sockFD, line, strlen(line));
    } while(n > 0);
    close(sockFD);
    return 0;
}
