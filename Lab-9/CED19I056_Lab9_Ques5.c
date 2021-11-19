//Implement producer consumer problem using semaphores

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include<time.h>

sem_t aArrived;
sem_t bArrived;

void *funA(void *arg)
{
    //Statement a1
    printf("This is a1 \n");
    sem_post(&aArrived);
    sem_wait(&bArrived);
    //Statement a2
    printf("This is a2 \n");
}

void *funB(void *arg)
{
    //Statement b1
    printf("This is b1 \n");
    sem_post(&bArrived);
    sem_wait(&aArrived);
    //Statement b2
    printf("This is b2 \n");
}

int main()
{
    pthread_t A,B;
    sem_init(&aArrived, 0, 0);
    sem_init(&bArrived, 0, 0);

    pthread_create(&A, NULL, funA, NULL);
    pthread_create(&B, NULL, funB, NULL);
    
    pthread_join(A, NULL);
    pthread_join(B, NULL);

    sem_destroy(&aArrived);
    sem_destroy(&bArrived);
    return 0;
}

