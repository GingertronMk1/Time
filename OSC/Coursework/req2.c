#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>

#define NUM_ITEMS   1000

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
    sem_wait(&prod_wait);
    while(1) {
        counter++;
        iIndex++;
        printf("P iIndex: %d\n", iIndex);
        //printSemValues();
        if (counter == NUM_ITEMS) {
            sem_post(&cons_wait);
            sem_post(&prod_wait);
            return NULL;
        }
    }
}

void *consumer(void *arg) {
    sem_wait(&cons_wait);
    while(1) {
        sem_wait(&prod_wait);
        iIndex--;
        int temp = iIndex;
        printf("C iIndex: %d\n", temp);
        //printSemValues();
        sem_post(&prod_wait);
        if (temp == 0) {
            return NULL;
        }
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;
    int check_prod, check_cons_1, check_cons_2;

    sem_init(&prod_wait, 0, 1);
    sem_init(&cons_wait, 0, 0);

    check_prod = pthread_create(&producer_thread, NULL, producer, NULL);
    if (check_prod) {
        printf("Error - pthread returned %d\n", check_prod);
        return 0;
    }
    check_cons_1 = pthread_create(&consumer_thread, NULL, consumer, NULL);
    if (check_cons_1) {
        printf("Error - pthread returned %d\n", check_cons_1);
        return 0;
    }
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    printSemValues();
    sem_destroy(&cons_wait);
    sem_destroy(&prod_wait);
    return 0;
}
