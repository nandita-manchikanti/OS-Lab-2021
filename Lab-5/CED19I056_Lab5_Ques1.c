//CED19I056
//Nandita M

#include<stdio.h>
#include<unistd.h>
#include<string.h>

//program to pass string using pipes
int main(){
    int pipefd1[2];//pipe file descriptors//[0] for reading and [1] for writing
    int pipefd2[2];//pipe file descriptors//[0] for reading and [1] for writing
    char p1wmsg[100];//buffer for writing to pipe
    char p1rmsg[100];//buffer for reading from pipe
    char p2wmsg[100];//buffer for writing to pipe
    char p2rmsg[100];//buffer for reading from pipe
    int pid;

    printf("Enter the string to be passed through pipe :");
    scanf("%s",p2wmsg);

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
        write(pipefd2[1],p2wmsg,sizeof(p2wmsg)+1);//write to pipe
        read(pipefd1[0],p1rmsg,sizeof(p1rmsg)+1);//read from pipe
        printf("Reversed String in child : %s\n",p1rmsg);
    }
    else{
        //child process
        close(pipefd1[0]);//close read end of pipe
        close(pipefd2[1]);//close write end of pipe
        read(pipefd2[0],p2rmsg,sizeof(p2rmsg)+1);//read from pipe
        int len = strlen(p2rmsg);
        for (int i = 0; i < len; i++)  
        {  
            p1wmsg[i] = p2rmsg[len - i - 1];  
        }
        p1wmsg[len] = '\0';
        write(pipefd1[1],p1wmsg,sizeof(p1wmsg)+1);//write to pipe
    }
    return 0;
}
