//CED19I056
//Nandita M

#include<stdio.h>
#include<unistd.h>
#include<string.h>

//program to pass string using pipes
int main(){
    int pipefd1[2];//pipe file descriptors//[0] for reading and [1] for writing
    int pipefd2[2];//pipe file descriptors//[0] for reading and [1] for writing
    int p1wmsg[100];//buffer for writing to pipe
    int p1rmsg[100];//buffer for reading from pipe
    int p2wmsg[100];//buffer for writing to pipe
    int p2rmsg[100];//buffer for reading from pipe
    int n;
    int pid;

    if(pipe(pipefd1)==-1){
        printf("Pipe creation failed\n");
        return 1;
    }
    if(pipe(pipefd2)==-1){
        printf("Pipe creation failed\n");
        return 1;
    }
    pid=fork();
    if(pid<0){
        printf("fork failed\n");
        return 1;
    }
    if(pid>0){
        //parent process
        close(pipefd1[1]);//close write end of pipe
        close(pipefd2[0]);//close read end of pipe
        printf("Enter the size of array : ");
        scanf("%d",&n);
        printf("Enter the elements of array:");
        for(int i=0;i<n;i++){
            scanf("%d",&p2wmsg[i]);
        }
        write(pipefd2[1],&p2wmsg,sizeof(p2wmsg));//write to pipe
        write(pipefd2[1],&n,sizeof(n));//write to pipe
        sleep(1);
        read(pipefd1[0],&p1rmsg,sizeof(p1rmsg));//read from pipe
        printf("The elements of array are : ");
        for(int i=0;i<n;i++){
            printf("\n%d -> %d",p2wmsg[i],p1rmsg[i]);
        }
        printf("\n");
    }
    else{
        //child process
        close(pipefd1[0]);//close read end of pipe
        close(pipefd2[1]);//close write end of pipe
        read(pipefd2[0],&p2rmsg,sizeof(p2rmsg));//read from pipe
        read(pipefd2[0],&n,sizeof(n));//read from pipe
        //Check if a number is amstrong number
        for(int i=0;i<n;i++){
            int sum=0;
            int temp=p2rmsg[i];
            while(temp!=0){
                int r=temp%10;
                sum=sum+(r*r*r);
                temp=temp/10;
            }
            if(sum==p2rmsg[i]){
                p1wmsg[i]=1;
            }
            else{
                p1wmsg[i]=0;
            }
        }
        write(pipefd1[1],&p1wmsg,sizeof(p1wmsg));//write to pipe
    }
    return 0;
}
