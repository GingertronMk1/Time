#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>

#define NUM_ITEMS   1000

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
    sem_wait(&sProdWait);
    while(1) {
        counter++;
        iIndex++;
        printf("P iIndex: %d\n", iIndex);
        //printSemValues();
        if (counter == NUM_ITEMS) {
            sem_post(&sConsWait);
            sem_post(&sProdWait);
            return NULL;
        }
    }
}

void *consumer(void *arg) {
    sem_wait(&sConsWait);
    while(1) {
        sem_wait(&sProdWait);
        iIndex--;
        int temp = iIndex;
        printf("C iIndex: %d\n", temp);
        //printSemValues();
        sem_post(&sProdWait);
        if (temp == 0) {
            return NULL;
        }
    }
}

int main() {
    pthread_t producerThread, consumerThread;
    int checkProd, checkCons;

    sem_init(&sProdWait, 0, 1);
    sem_init(&sConsWait, 0, 0);

    checkProd = pthread_create(&producerThread, NULL, producer, NULL);
    if (checkProd) {
        printf("Error - pthread returned %d\n", checkProd);
        return 0;
    }
    checkCons = pthread_create(&consumerThread, NULL, consumer, NULL);
    if (checkCons) {
        printf("Error - pthread returned %d\n", checkCons);
        return 0;
    }
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    printSemValues();
    sem_destroy(&sConsWait);
    sem_destroy(&sProdWait);
    return 0;
}
