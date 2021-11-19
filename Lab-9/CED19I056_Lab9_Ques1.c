#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <stdint.h>

int sum[5];

void* thread_fun(void* arg){
    int id = (intptr_t) arg;
    int start=id*200;
    int i=0;

    while(i<200){
        sum[id]+=(start+i);
        i++;
    }
    return NULL;
}

int main(){
    pthread_t t1,t2,t3,t4,t5;

    pthread_create(&t1,NULL,thread_fun,(void*)(intptr_t)0);
    pthread_create(&t2,NULL,thread_fun,(void*)(intptr_t)1);
    pthread_create(&t3,NULL,thread_fun,(void*)(intptr_t)2);
    pthread_create(&t4,NULL,thread_fun,(void*)(intptr_t)3);
    pthread_create(&t5,NULL,thread_fun,(void*)(intptr_t)4);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    pthread_join(t5,NULL);
    
    printf("Sum of first 1000 numbers using 5 threads is %d\n",sum[0]+sum[1]+sum[2]+sum[3]+sum[4]);
    return 0;
}