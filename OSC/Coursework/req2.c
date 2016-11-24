#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE    100
#define NUM_ITEMS   1000

char charArray[BUF_SIZE];

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
        counter++;
        current_items++;
        printf("iIndex: %d\t%s\n", current_items, charArray);
        sem_post(&prod_wait);
    }
    return NULL;
}

void *consumer(void *arg) {
    int temp, i, loops;
    char space = ' ';
    for(loops = 0; loops < NUM_ITEMS ; loops++) {
        sem_wait(&prod_wait);
        current_items--;
        temp = current_items;
        printf("iIndex: %d\t%s\n", temp, charArray);
        sem_post(&cons_wait);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread_1, consumer_thread_2;
    int check_prod, check_cons_1, check_cons_2;

    sem_init(&prod_wait, 0, 0);
    sem_init(&cons_wait, 0, BUF_SIZE);

    check_prod = pthread_create(&producer_thread, NULL, producer, NULL);
    if (check_prod) {
        printf("Error - pthread returned %d\n", check_prod);
        return 0;
    }
    check_cons_1 = pthread_create(&consumer_thread_1, NULL, consumer, NULL);
    if (check_cons_1) {
        printf("Error - pthread returned %d\n", check_cons_1);
        return 0;
    }
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread_1, NULL);

    printf("prod_wait: %d\n", getSemValue(prod_wait));
    printf("cons_wait: %d\n", getSemValue(cons_wait));
    sem_destroy(&cons_wait);
    sem_destroy(&prod_wait);
    return 0;
}
