#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <stdint.h>

void* thread_fun(void* arg){
    int n = (intptr_t) arg;
    for(int i=0;i <= n ;i++){
        printf(" %d",i);
    }
}

int main(){
    pthread_t t1;
    int n;
    printf("Enter the value of n :");
    scanf("%d",&n);
    pthread_create(&t1,NULL,thread_fun,(void *)(intptr_t)n);
    pthread_join(t1,NULL);
    return 0;
}