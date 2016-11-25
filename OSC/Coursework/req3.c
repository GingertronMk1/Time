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
        if (iIndex < BUF_SIZE) {
            charArray[iIndex++] = '*';
            counter++;
        } else {
            sem_post(&cons_wait);
            //printf("Producer waiting...\n");
            sem_wait(&prod_wait);
        }
        printf("P iIndex: %d\tCounter: %d\t%s\n", iIndex, counter, charArray);
        //printSemValues();
        if (counter == NUM_ITEMS) {
            //printf("Exiting producer\n");
            sem_post(&cons_wait);
            return NULL;
        }
    }
}

void *consumer(void *arg) {
    int temp_counter;
    sem_wait(&prod_wait);
    while(1) {
        temp_counter = counter;
        if (iIndex > 0) {
            charArray[iIndex--] = ' ';
        } else {
            sem_post(&prod_wait);
            //printf("Consumer waiting...\n");
            sem_wait(&cons_wait);
        }
        printf("C iIndex: %d\tCounter: %d\t%s\n", iIndex, temp_counter, charArray);
        //printSemValues();
        if (counter == NUM_ITEMS && iIndex == 0) {
            //printf("Exiting consumer\n");
            return NULL;
        }
    }
}

int main() {
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
    sem_destroy(&cons_wait);
    sem_destroy(&prod_wait);
    return 0;
}
