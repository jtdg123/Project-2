#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX 5

sem_t full, empty;
pthread_mutex_t mutex;
int buffer[MAX];
int in = 0, out = 0;

void* producer(void* arg) {
    int id = *((int*)arg);
    for (int i = 0; i < 5; i++) {
        sleep(rand() % 3);
        int item = rand() % 100;

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("[Producer %d] Produced item: %d at index %d\n", id, item, in);
        in = (in + 1) % MAX;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    int id = *((int*)arg);
    for (int i = 0; i < 5; i++) {
        sleep(rand() % 3);

        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("[Consumer %d] Consumed item: %d at index %d\n", id, item, out);
        out = (out + 1) % MAX;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t prod[2], cons[2];
    int ids[2] = {1, 2};

    sem_init(&full, 0, 0);
    sem_init(&empty, 0, MAX);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 2; i++) {
        pthread_create(&prod[i], NULL, producer, &ids[i]);
        pthread_create(&cons[i], NULL, consumer, &ids[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(prod[i], NULL);
        pthread_join(cons[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}
