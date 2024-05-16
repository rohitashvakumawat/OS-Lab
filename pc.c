#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
typedef int buffer_item;

buffer_item buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t sem;
sem_t empty;
sem_t full;

void *producer(void *param){
    buffer_item item;
    while(1){
        item = rand() % 1000;
        sem_wait(&empty); // Wait for an empty slot and decrement empty
        sem_wait(&sem); // Acquire lock
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        sem_post(&sem); // Release lock
        sem_post(&full); // Increment full slots count
        printf("Producer produced item: %d\n", item);
        sleep(1);
    }
}

void *consumer(void *param){
    buffer_item item;
    while(1){
        sem_wait(&full); // Wait for a filled slot and idecrement full slots count
        sem_wait(&sem); // Acquire lock
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&sem); // Release lock
        sem_post(&empty); // Increment empty count
        printf("Consumer consumed item: %d\n", item);
        sleep(2);
    }
}

int main(){
    pthread_t tid_producer, tid_consumer;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    sem_init(&sem, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_create(&tid_producer, &attr, producer, NULL);
    pthread_create(&tid_consumer, &attr, consumer, NULL);

    // Join threads to main thread
    pthread_join(tid_producer, NULL);
    pthread_join(tid_consumer, NULL);

    return 0;
}
