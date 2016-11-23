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
        charArray[current_items++] = star;
        counter++;
        printf("%s\n", charArray);
        sem_post(&prod_wait);
    }
    return NULL;
}

void *consumer(void *arg) {
    int temp, i, loops;
    char space = ' ';
    for(loops = 0; loops < NUM_ITEMS ; loops++) {
        sem_wait(&prod_wait);
        charArray[current_items--] = space;
        temp = current_items;
        printf("%s\n", charArray);
        sem_post(&cons_wait);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;
    int check_prod, check_cons;

    sem_init(&prod_wait, 0, 0);
    sem_init(&cons_wait, 0, BUF_SIZE);

    check_prod = pthread_create(&producer_thread, NULL, producer, NULL);
    if (check_prod) {
        printf("Error - pthread returned %d\n", check_prod);
        return 0;
    } else {
        printf("Producer thread looks good\n");
    }
    check_cons = pthread_create(&consumer_thread, NULL, consumer, NULL);
    if (check_cons) {
        printf("Error - pthread returned %d\n", check_cons);
        return 0;
    } else {
        printf("Consumer thread looks good\n");
    }
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    //pthread_exit(NULL);
    printf("prod_wait: %d\n", getSemValue(prod_wait));
    printf("cons_wait: %d\n", getSemValue(cons_wait));
    sem_destroy(&cons_wait);
    sem_destroy(&prod_wait);
    return 0;
}
