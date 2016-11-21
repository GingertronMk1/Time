#include <stdio.h>
#include <sys/time.h>

#define NUMBER_OF_JOBS 10
#define JOB_INDEX 0
#define BURST_TIME 1
#define REMAINING_TIME 2
#define PRIORITY 3

int aiJobs[NUMBER_OF_JOBS][4];

void generateJobs()
{
    int i;
    for(i = 0; i < NUMBER_OF_JOBS;i++)
    {
        aiJobs[i][JOB_INDEX] = i;
        aiJobs[i][BURST_TIME] = rand() % 99 + 1;
        aiJobs[i][REMAINING_TIME] = aiJobs[i][BURST_TIME];
        aiJobs[i][PRIORITY] = rand()%10;
    }
}

void printJob(int iId, int iBurstTime, int iRemainingTime, int iPriority)
{
    printf("Id = %d, Burst Time = %d, Remaining Time = %d, Priority = %d\n", iId, iBurstTime, iRemainingTime, iPriority);
}

void printJobs()
{
    int i;
    printf("JOBS: \n");
    for(i = 0; i < NUMBER_OF_JOBS; i++)
        printJob(aiJobs[i][JOB_INDEX], aiJobs[i][BURST_TIME], aiJobs[i][REMAINING_TIME], aiJobs[i][PRIORITY]);
}

long int getDifferenceInMilliSeconds(struct timeval start, struct timeval end)
{
    int iSeconds = end.tv_sec - start.tv_sec;
    int iUSeconds = end.tv_usec - start.tv_usec;
    long int mtime = (iSeconds * 1000 + iUSeconds / 1000.0);
    return mtime;
}

void simulateJob(int iTime)
{
    long int iDifference = 0;
    struct timeval startTime, currentTime;
    gettimeofday(&startTime, NULL);
    do
    {   
        gettimeofday(&currentTime, NULL);
        iDifference = getDifferenceInMilliSeconds(startTime, currentTime);
    } while(iDifference < iTime);
}



int main()
{
    generateJobs();
    printJobs();

    return 0;
}


