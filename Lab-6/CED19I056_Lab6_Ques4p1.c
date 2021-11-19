//CED19I056
//Nandita M

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <time.h>

int main()
{   int shm=0;

    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    char *str = (char*) shmat(shmid,(void*)0,0);
    char *temp = (char*) shmat(shmid,(void*)0,0)+1024;
    char *flag=(char*) shmat(shmid,(void*)0,0)+2048;
    printf("\nEnter the string to be stored in shared memory\n");
    scanf("%s",str);
        
    while (*temp != '*')
        sleep(1);

    if(*flag=='1'){
        printf("The string is not a palindrome\n");
    }else{
        printf("The string is a palindrome\n");
    }
    shmdt(str);
    shmdt(temp);
    shmdt(flag);

    return 0;
}