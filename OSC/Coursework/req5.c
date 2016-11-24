#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define BUF_SIZE        100
#define NUM_ITEMS       1000
#define NUM_CONSUMERS   5

char charArray[BUF_SIZE];

/* JOB CREATION, SIMULATION, DELETION STUFF HERE
 * BASICALLY REQS 1A, 1B
 */

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


/* SEMAPHORE, PRODUCER, CONSUMER STUFF HERE
 * BASICALLY REQS 2-4
 */

int current_items = 0;
int counter = 0;

sem_t prod_wait;
sem_t cons_wait;

int getSemValue(sem_t semaphore) {
    int semValue;
    sem_getvalue(&semaphore, &semValue);
    return semValue;
}

void *producer(void *arg) {
    int loops;
    char star = '*';
    for(loops = 0; loops < NUM_ITEMS ; loops++) {
        sem_wait(&cons_wait);
        unsigned int thread_id = pthread_self();
        charArray[current_items++] = star;
        counter++;
        printf("Producer tID: %u\tiIndex: %d\t%s\n", thread_id, current_items, charArray);
        sem_post(&prod_wait);
    }
    return NULL;
}

void *consumer(void *arg) {
    int temp, i, loops, consumerno;
    char space = ' ';
    for(loops = 0; loops < NUM_ITEMS/NUM_CONSUMERS ; loops++) {
        sem_wait(&prod_wait);
        unsigned int thread_id = pthread_self();
        charArray[current_items--] = space;
        temp = current_items;
        printf("Consumer tID: %u\tiIndex: %d\t%s\n", thread_id, temp, charArray);
        sem_post(&cons_wait);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread;
    pthread_t consumers[NUM_CONSUMERS];
    int i, check_thread;

    sem_init(&prod_wait, 0, 0);
    sem_init(&cons_wait, 0, BUF_SIZE);

    pthread_create(&producer_thread, NULL, producer, NULL);

    for (i = 0; i < NUM_CONSUMERS; i++) {
        check_thread = pthread_create(&consumers[i], NULL, consumer, NULL);
        if (check_thread) {
            printf("Error - pthread returned %d\n", check_thread);
            return 0;
        } else {
            printf("Consumer %d fine\n", i+1);
        }
    }

    pthread_join(producer_thread, NULL);

    for (i=0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    printf("prod_wait: %d\n", getSemValue(prod_wait));
    printf("cons_wait: %d\n", getSemValue(cons_wait));
    sem_destroy(&cons_wait);
    sem_destroy(&prod_wait);
    return 0;
}
