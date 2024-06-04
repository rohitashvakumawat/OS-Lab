#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <semaphore.h>

sem_t chopstick[5];

void *philosopher(void *arg) {
    int id = *((int *)arg);

    while (true) {
        // Thinking
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);

        // Attempt to pick up chopsticks
        sem_wait(&chopstick[id]);
        sem_wait(&chopstick[(id + 1) % 5]);

        // Eating
        printf("Philosopher %d is eating.\n", id);
        sleep(1);

        // Release chopsticks
        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id + 1) % 5]);

        printf("Philosopher %d is done eating, thinking now.\n", id);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[5];
    int ids[5] = {0, 1, 2, 3, 4};

    for (int i = 0; i < 5; i++) {
        sem_init(&chopstick[i], 0, 1); // Initialize each semaphore to 1 (available)
    }

    for (int i = 0; i < 5; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < 5; i++) {
        sem_destroy(&chopstick[i]); // Destroy semaphores
    }

    return 0;
}
