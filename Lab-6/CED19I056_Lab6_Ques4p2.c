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
    char *flag=(char*) shmat(shmid,(void*)0,0)+2048;

    printf("Data read from memory: %s\n",str);
    //check if str is a palindrome
    int i,j;
    *flag='0';
    for(i=0,j=strlen(str)-1;i<j;i++,j--)
    {
        if(str[i]!=str[j])
        {
            *flag='1';
            break;
        }
    }

    *temp='*';
    //detach from shared memory 
    shmdt(str);
    shmdt(temp);
    shmdt(flag);
    
    // destroy the shared memory
    shmctl(shmid,IPC_RMID,NULL);
     
    return 0;
}