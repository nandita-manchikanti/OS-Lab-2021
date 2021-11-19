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
    
    printf("Write Data : ");
    scanf("%s",str);	
    
    while (*temp != '*')
        sleep(1);

    printf("Data read in memory: %s\n",str);
    shmdt(str);
    shmdt(temp);
  
    return 0;
}