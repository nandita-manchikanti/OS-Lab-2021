#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
//sort the array in acending order in parent process and print the array in child process using fork

int array[10];
int n;
int status;
void ascending();
void descending();

int main()
{
  int pid;
  int i,j;
  int n;

  printf("\nEnter the size of array :");
  scanf("%d",&n);

  printf("\nEnter the elements:");
  for(i=0;i<n;i++){
    scanf("%d",&array[i]);
  }
 
  pid=fork();
    
  if(pid>0)
  {
    waitpid(pid,&status,0);
    printf("\nParent process");
    int i,j,k,temp;
   for(i=0;i<n;i++)
  {
    for(j=i+1;j<n;j++)
    {
        if(array[i]>array[j])
        {
            temp=array[i];
            array[i]=array[j];
            array[j]=temp;  
        }
    }
   }

    printf("The numbers in Ascending order are:\n");
    for(i=0;i<n;i++){
        printf("%d\t",array[i]);
    }
    printf("\n");
  }
    else if(pid==0){
    printf("\nChild process");
    int i,j,k,temp;
    for(i=0;i<n;i++)
  {
    for(j=i+1;j<n;j++)
    {
        if(array[i]<array[j])
        {
            temp=array[i];
            array[i]=array[j];
            array[j]=temp;
        }
    }
   }

    printf("The numbers in Descending order are:\n");
    for(i=0;i<n;i++){
        printf("%d\t",array[i]);
    }
    printf("\n");
  }
  return 0;
}

