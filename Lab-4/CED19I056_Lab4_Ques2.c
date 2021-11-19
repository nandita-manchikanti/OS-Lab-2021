#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
int main(void)
{
     char *binaryPath1 = "ls";
     char *binaryPath2 = "pstree";
     execlp(binaryPath1, binaryPath1, NULL, NULL, NULL);
     execlp(binaryPath2, binaryPath2, NULL, NULL, NULL);
     return 0;
}
