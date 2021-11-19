#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
   int stat;
   if(fork() == 0)
   {
       exit(1);
   }
   else
   {
       wait(&stat);
   }
   if(WIFEXITED(stat))
   {
       printf("Exit status: %d\n",WEXITSTATUS(stat));
   }
   else if(WIFSIGNALED(stat))
   {
       psignal(WTERMSIG(stat), "Exit signal");
   }
}
