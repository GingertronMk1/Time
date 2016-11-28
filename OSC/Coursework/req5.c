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
int start_timer = 0;

sem_t prod_wait;
sem_t cons_wait;

void printSemValues() {
    int prodValue, consValue;
    sem_getvalue(&prod_wait, &prodValue);
    sem_getvalue(&cons_wait, &consValue);
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
            sem_post(&cons_wait);
        } else {
            sem_post(&cons_wait);
            sem_wait(&prod_wait);
        }
        if (counter == NUM_ITEMS && iIndex == 0) {
            return NULL;
        }
    }
}

void *consumer(void *arg) {
    int temp_counter, array_mover;
    sem_wait(&prod_wait);
    while(1) {
        temp_counter = counter;
        if (iIndex > 0) {
            simulateJob(aiJobs[1][REMAINING_TIME]);
            start_timer += aiJobs[0][REMAINING_TIME];
            printf("Removing:\t");
            printf("JOB ID: %d Burst Time: %d Start Time: %d", aiJobs[1][JOB_INDEX], aiJobs[1][BURST_TIME], start_timer);
            printf(" (Jobs Produced: %d, Jobs In Buffer: %d)\n", counter, --iIndex);
            for (array_mover = 0; array_mover < BUF_SIZE;) {
                memcpy(aiJobs[array_mover], aiJobs[++array_mover], sizeof(aiJobs[++array_mover]));
            }
            sem_wait(&cons_wait);
        } else {
            sem_post(&prod_wait);
            sem_wait(&cons_wait);
        }
        if (counter == NUM_ITEMS && iIndex == 0) {
            sem_post(&prod_wait);
            return NULL;
        }
    }
}

int main() {
    // Production/Consumption Stuff
    pthread_t producer_thread, consumer_thread;
    int check_prod, check_cons;

    sem_init(&prod_wait, 0, 1);
    sem_init(&cons_wait, 0, 0);
    printSemValues();

    check_prod = pthread_create(&producer_thread, NULL, producer, NULL);
    if (check_prod) {
        printf("Error - pthread returned %d\n", check_prod);
        return 0;
    } else {
        //printf("Producer thread OK\n");
    }
    check_cons = pthread_create(&consumer_thread, NULL, consumer, NULL);
    if (check_cons) {
        printf("Error - pthread returned %d\n", check_cons);
        return 0;
    } else {
        //printf("Consumer thread OK\n");
    }

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    printSemValues();
    double avg_start_time = (start_timer*1.00)/NUM_ITEMS;
    printf("Start Time: %d Number of Jobs: %d Avg Start Time: %.2f\n", start_timer, NUM_ITEMS, avg_start_time);
    sem_destroy(&cons_wait);
    sem_destroy(&prod_wait);
    return 0;
}
