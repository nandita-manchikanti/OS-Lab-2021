//CED19I056
//Nandita M

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
  
int main()
{  
    // ftok to generate unique key
    key_t key = ftok("shmfile",65);
  
    // shmget returns an identifier in shmid
    int shmid = shmget(key,1024,0666|IPC_CREAT);
  
    // shmat to attach to shared memory
    char *str = (char*) shmat(shmid,(void*)0,0);
    char *temp = (char*) shmat(shmid,(void*)0,0)+1024;

    printf("Data read from memory: %s\n",str);

    printf("Write Data : ");
    scanf("%s",str);
    
    *temp = '*';
    //detach from shared memory 
    shmdt(str);
    shmdt(temp);
    
    // destroy the shared memory
    shmctl(shmid,IPC_RMID,NULL);
     
    return 0;
}