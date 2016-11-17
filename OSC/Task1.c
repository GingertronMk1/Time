#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_PROCESSES 4

int main() {
    pid_t pid = 0;
    int cID = 0;
    for(int i = 0; i < NUMBER_OF_PROCESSES; i++){
        pid = fork();
        if(pid < 0) {
            printf("Could not create process\n");
            exit(1);
        } else if(pid == 0) {
            cID++;
            printf("Hello from the child process %d with pID %d\n", i, getpid());
            break;
        } else if(pid > 0) {
            printf("Hello from the parent process with pID %d\n", pid);
        }
    }
    return 0;
}
