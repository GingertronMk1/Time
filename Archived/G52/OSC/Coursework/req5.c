#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define BUF_SIZE        100
#define NUM_ITEMS       1000
#define JOB_INDEX       0
#define BURST_TIME      1
#define REMAINING_TIME  2
#define PRIORITY        3

/* JOB CREATION, SIMULATION, DELETION STUFF HERE
 * BASICALLY REQS 1A, 1B
 */

int aiJobs[BUF_SIZE][4];

void generateJobs()
{
    int i;
    for(i = 0; i < BUF_SIZE;i++)
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
    for(i = 0; i < BUF_SIZE; i++)
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


/* SEMAPHORE, PRODUCER, CONSUMER STUFF HERE
 * BASICALLY REQS 2-4
 */

int iIndex = 0;
int counter = 0;
int startTimer = 0;

sem_t sProdWait;
sem_t sConsWait;

void printSemValues() {
    int prodValue, consValue;
    sem_getvalue(&sProdWait, &prodValue);
    sem_getvalue(&sConsWait, &consValue);
    printf("P: %d C: %d\n", prodValue, consValue);
}

void *producer(void *arg) {
    while(1) {
        if (iIndex < BUF_SIZE && counter < NUM_ITEMS) {
            aiJobs[++iIndex][JOB_INDEX] = counter++;
            aiJobs[iIndex][BURST_TIME] = rand() % 99 + 1;
            aiJobs[iIndex][REMAINING_TIME] = aiJobs[iIndex][BURST_TIME];
            aiJobs[iIndex][PRIORITY] = rand()%10;
            printf("Producing:\t");
            printf("JOB ID: %d Burst Time: %d Remaining Time: %d", aiJobs[iIndex][JOB_INDEX], aiJobs[iIndex][BURST_TIME], aiJobs[iIndex][REMAINING_TIME]);
            printf(" (Jobs Produced: %d, Jobs In Buffer: %d)\n", counter, iIndex);
            sem_post(&sConsWait);
        } else {
            sem_post(&sConsWait);
            sem_wait(&sProdWait);
        }
        if (counter == NUM_ITEMS && iIndex == 0) {
            return NULL;
        }
    }
}

void *consumer(void *arg) {
    int tempCounter, arrayMover;
    sem_wait(&sProdWait);
    while(1) {
        tempCounter = counter;
        if (iIndex > 0) {
            simulateJob(aiJobs[1][REMAINING_TIME]);
            startTimer += aiJobs[0][REMAINING_TIME];
            printf("Removing:\t");
            printf("JOB ID: %d Burst Time: %d Start Time: %d", aiJobs[1][JOB_INDEX], aiJobs[1][BURST_TIME], startTimer);
            printf(" (Jobs Produced: %d, Jobs In Buffer: %d)\n", counter, --iIndex);
            for (arrayMover = 0; arrayMover < BUF_SIZE;) {
                memcpy(aiJobs[arrayMover], aiJobs[++arrayMover], sizeof(aiJobs[++arrayMover]));
            }
            sem_wait(&sConsWait);
        } else {
            sem_post(&sProdWait);
            sem_wait(&sConsWait);
        }
        if (counter == NUM_ITEMS && iIndex == 0) {
            sem_post(&sProdWait);
            return NULL;
        }
    }
}

int main() {
    // Production/Consumption Stuff
    pthread_t producerThread, consumerThread;
    int checkProd, checkCons;

    sem_init(&sProdWait, 0, 1);
    sem_init(&sConsWait, 0, 0);
    printSemValues();

    checkProd = pthread_create(&producerThread, NULL, producer, NULL);
    if (checkProd) {
        printf("Error - pthread returned %d\n", checkProd);
        return 0;
    } else {
        //printf("Producer thread OK\n");
    }
    checkCons = pthread_create(&consumerThread, NULL, consumer, NULL);
    if (checkCons) {
        printf("Error - pthread returned %d\n", checkCons);
        return 0;
    } else {
        //printf("Consumer thread OK\n");
    }

    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);
    printSemValues();
    double avgStartTime = (startTimer*1.00)/NUM_ITEMS;
    printf("Start Time: %d Number of Jobs: %d Avg Start Time: %.2f\n", startTimer, NUM_ITEMS, avgStartTime);
    sem_destroy(&sConsWait);
    sem_destroy(&sProdWait);
    return 0;
}
