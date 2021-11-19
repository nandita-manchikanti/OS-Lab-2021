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
        //sort p2wmsg in ascending order
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(p2wmsg[i]>p2wmsg[j]){
                    int temp=p2wmsg[i];
                    p2wmsg[i]=p2wmsg[j];
                    p2wmsg[j]=temp;
                }
            }
        }
        write(pipefd2[1],&p2wmsg,sizeof(p2wmsg)+1);//write to pipe
        write(pipefd2[1],&n,sizeof(n));//write to pipe
        sleep(4);
        read(pipefd1[0],&p1rmsg,sizeof(p1rmsg)+1);//read from pipe
        printf("Descending Order of the array in parent \n");
        for(int i=0;i<n;i++){
            printf("%d ",p1rmsg[i]);
        }
        printf("\n");
    }
    else{
        //child process
        close(pipefd1[0]);//close read end of pipe
        close(pipefd2[1]);//close write end of pipe
        read(pipefd2[0],&p2rmsg,sizeof(p2rmsg)+1);//read from pipe
        read(pipefd2[0],&n,sizeof(n));//read from pipe
        printf("Acending Order of the array in child \n");
        for(int i=0;i<n;i++){
            printf("%d ",p2rmsg[i]);
        }
        printf("\n");
        //sort p2rmsg in descending order
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(p2rmsg[i]<p2rmsg[j]){
                    int temp=p2rmsg[i];
                    p2rmsg[i]=p2rmsg[j];
                    p2rmsg[j]=temp;
                }
            }
        }
        write(pipefd1[1],&p2rmsg,sizeof(p2rmsg)+1);//write to pipe
    }
    return 0;
}
