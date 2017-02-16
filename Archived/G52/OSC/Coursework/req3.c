#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE    100
#define NUM_ITEMS   1000

char charArray[BUF_SIZE];

int iIndex = 0;
int counter = 0;

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
        if (iIndex < BUF_SIZE) {
            charArray[iIndex++] = '*';
            counter++;
        } else {
            sem_post(&sConsWait);
            //printf("Producer waiting...\n");
            sem_wait(&sProdWait);
        }
        printf("P iIndex: %d\tCounter: %d\t%s\n", iIndex, counter, charArray);
        //printSemValues();
        if (counter == NUM_ITEMS) {
            //printf("Exiting producer\n");
            sem_post(&sConsWait);
            return NULL;
        }
    }
}

void *consumer(void *arg) {
    int tempCounter;
    sem_wait(&sProdWait);
    while(1) {
        tempCounter = counter;
        if (iIndex > 0) {
            charArray[iIndex--] = ' ';
        } else {
            sem_post(&sProdWait);
            //printf("Consumer waiting...\n");
            sem_wait(&sConsWait);
        }
        printf("C iIndex: %d\tCounter: %d\t%s\n", iIndex, tempCounter, charArray);
        //printSemValues();
        if (counter == NUM_ITEMS && iIndex == 0) {
            //printf("Exiting consumer\n");
            return NULL;
        }
    }
}

int main() {
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
    sem_destroy(&sConsWait);
    sem_destroy(&sProdWait);
    return 0;
}
