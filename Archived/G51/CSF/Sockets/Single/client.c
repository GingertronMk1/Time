//  Name:       Jack Ellis
//  Username:   psyje5
//  Student ID: 4262333

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

#define NETBUFSIZE      12
#define kQUOTEPORT      1717
#define kMULTIQUOTEPORT 1818

void serverConnection(int sockFD, struct sockaddr_in sad, char *buf, int n, int more);

int main(int argc, const char * argv[]){
    char buf[NETBUFSIZE+1];
    char line[128];
    ssize_t n;
    int more;

    int sockFD;
    int port;
    struct sockaddr_in sad;
    struct hostent *ptrh;


    sockFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    memset(&sad, 0, sizeof(sad));                       /* Sets every byte of the address to be zero */
    sad.sin_family = AF_INET;

    /* Look up name */
    ptrh = gethostbyname(argv[1]);
    memcpy(&sad.sin_addr, ptrh->h_addr, ptrh->h_length);

    /* Set port */
    port = kQUOTEPORT;
    sad.sin_port = htons(port);

    serverConnection(sockFD, sad, buf, n, more);

    close(sockFD);

    return 0;
}

void serverConnection(int sockFD, struct sockaddr_in sad, char *buf, int n, int more){
    connect(sockFD, (struct sockaddr *)&sad, sizeof(sad));
    do
    {
        more = 1;
        n = read(sockFD, buf, NETBUFSIZE);
        buf[n] = '\0';

        for(int i = 0; i < n; i++)
        {
            if(buf[i] == 10)
            {
                more = 0;
                break;
            }
        }

        printf("%s", buf);
    } while(more);

}
