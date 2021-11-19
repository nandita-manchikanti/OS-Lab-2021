#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <stdint.h>

void* thread_fun(void* arg){
    int *array=(int *)arg;
    int sum = 0;
    for(int i=0;i<10;i++){
        sum=sum+array[i];
    }
    return (void *)sum;
}

int main(){
    pthread_t t1;
    int n;
    int sum;
    int array[10];
    printf("Enter the 10 numbers :");
    for(int i=0;i<10;i++){
        scanf("%d",&array[i]);
    }
    pthread_create(&t1,NULL,thread_fun,(void *)array);
    pthread_join(t1,(void *)&sum);
    printf("Sum of the numbers is %d\n",sum);
    return 0;
}