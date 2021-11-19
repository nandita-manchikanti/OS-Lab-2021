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

    char string1[100];
    char string2[100];

    printf("Enter the string1 to be passed through pipe :");
    scanf("%s",p1wmsg);

    

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
        close(pipefd1[0]);//close read end of pipe1
        close(pipefd2[1]);//close write end of pipe2
        write(pipefd1[1],p1wmsg,sizeof(p1wmsg)+1);//write to pipe1
        read(pipefd2[0],p2wmsg,sizeof(p2wmsg)+1);//read from pipe2
        printf("concatenated String : %s\n",p2wmsg);
    }
    else{
        //child process
        close(pipefd1[1]);
        close(pipefd2[0]);
        read(pipefd1[0],p1rmsg,sizeof(p1rmsg)+1);//read from pipe1
        printf("Enter the string2 to be passed through pipe :");
        scanf("%s",string2);
        strcpy(p2wmsg,p1rmsg);
        strcat(p2wmsg,string2);
        write(pipefd2[1],p2wmsg,sizeof(p2wmsg)+1);//write to pipe2
    }
    return 0;
}
