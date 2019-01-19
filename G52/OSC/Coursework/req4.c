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

int iIndex = 0;
int counter = 0;

sem_t prod_wait;
sem_t cons_wait;
sem_t cons_count;

void printSemValues() {
    int prodValue, consValue, countValue;
    sem_getvalue(&prod_wait, &prodValue);
    sem_getvalue(&cons_wait, &consValue);
    sem_getvalue(&cons_count, &countValue);
    printf("P: %d C: %d Count: %d\n", prodValue, consValue, countValue);
}

void *producer(void *arg) {
    int i;
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
        printSemValues();
        if (counter == NUM_ITEMS) {
            //printf("Exiting producer\n");
            for (i = 0; i < NUM_CONSUMERS; i++) {
                sem_post(&cons_count);
            }
            return NULL;
        }
    }
}

void *consumer(void *arg) {
    int temp_counter;
    sem_wait(&cons_wait);
    while(1) {
        sem_wait(&cons_count);
        sem_wait(&cons_wait);
        int thread_id = pthread_self();
        temp_counter = counter;
        if (iIndex > 0) {
            charArray[iIndex--] = ' ';
        } else {
            sem_post(&prod_wait);
            sem_wait(&cons_wait);
        }
        printf("C iIndex: %d\tCounter: %d\t%s\n", iIndex, temp_counter, charArray);
        printSemValues();
        if (counter == NUM_ITEMS && iIndex == 0) {
            printf("Exiting consumer %d\n", thread_id);
            return NULL;
        }
    }
}

int main() {
    pthread_t producer_thread, consumer_thread[NUM_CONSUMERS];
    int check_prod, check_cons, cons_number;

    sem_init(&prod_wait, 0, 1);
    sem_init(&cons_wait, 0, 0);
    sem_init(&cons_count, 0, NUM_CONSUMERS);
    printSemValues();

    check_prod = pthread_create(&producer_thread, NULL, producer, NULL);
    if (check_prod) {
        printf("Error - pthread returned %d\n", check_prod);
        return 0;
    } else {
        //printf("Producer thread OK\n");
    }
    for (cons_number = 0; cons_number < NUM_CONSUMERS; cons_number++) {
        check_cons = pthread_create(&consumer_thread[cons_number], NULL, consumer, NULL);
        if (check_cons) {
            printf("Error - pthread returned %d\n", check_cons);
            return 0;
        } else {
            printf("Consumer thread %d OK\n", cons_number);
        }
    }

    pthread_join(producer_thread, NULL);

    for (cons_number = 0; cons_number < NUM_CONSUMERS; cons_number++) {
        pthread_join(consumer_thread[cons_number], NULL);
    }

    printSemValues();
    sem_destroy(&cons_wait);
    sem_destroy(&prod_wait);
    return 0;
}
