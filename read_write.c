#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdbool.h>

sem_t wrt;
sem_t sem;
int readcount = 0;

void *reader(void *arg){
    while(true){
        sem_wait(&sem); // Lock the sem to protect readcount
        readcount++;
        if(readcount == 1) // First reader, lock writer
            sem_wait(&wrt);
        sem_post(&sem); // Release sem

        printf("\nReading now...");

        sem_wait(&sem); // Lock the sem again to protect readcount
        readcount--;
        if(readcount == 0) // Last reader, release writer
            sem_post(&wrt);
        sem_post(&sem); // Release sem

        printf("\nDone Reading.");
    }
    return NULL;
}

void *writer(void *arg){
    while(true){
        sem_wait(&wrt); // Lock writer
        printf("\nWriting now...");

        sem_post(&wrt); // Release writer

        printf("\nDone writing.");
    }
    return NULL;
}

int main(){
    pthread_t tid_reader, tid_writer;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    sem_init(&sem, 0, 1);
    sem_init(&wrt, 0, 1);

    pthread_create(&tid_reader, &attr, reader, NULL);
    pthread_create(&tid_writer, &attr, writer, NULL);

    pthread_join(tid_reader, NULL);
    pthread_join(tid_writer, NULL);

    return 0;
}
