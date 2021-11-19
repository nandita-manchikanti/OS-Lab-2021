#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#define BufferSize 5

pthread_mutex_t mutex;
sem_t full, empty;
int count,in,out;

void *producer(void *arg)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        count++;    
        in = (in + 1) % BufferSize;
        printf("Producer produced item %d\n", i);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *arg)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        count--;
        out = (out + 1) % BufferSize;
        printf("Consumer consumed item %d\n", i);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main()
{
    pthread_t prod, cons;
    count = 0;
    in = 0;
    out = 0;
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BufferSize);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&full);
    sem_destroy(&empty);
    pthread_mutex_destroy(&mutex);
    return 0;
}

