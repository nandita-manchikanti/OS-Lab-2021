//CED19I056
//Nandita M

//Example 1
#include <stdio.h>
#include <dirent.h>
int main(void)
{
    struct dirent *de;
    DIR *dr = opendir("./OSLab");
    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return 0;
    }
    // for readdir()
    while ((de = readdir(dr)) != NULL)
            printf("%s\n", de->d_name);
  
    closedir(dr);    
    return 0;
}

//Example 2
#include<stdio.h>
#include <stdlib.h>
#include <fcntl.h>
int main()
{
    int fd1 = open("Ques1.c", O_RDONLY );
    if (fd1 < 0)
    {
        printf("Could not open file\n");
        exit(1);
    }
    printf("opened the fd = % d\n", fd1);
    if (close(fd1) < 0)
    {
        printf("Could not close file\n");
        exit(1);
    }
    printf("closed the fd.\n");
}


//Example 3
#include<unistd.h>
int main()
{
    char buff[20];
    read(0,buff,10);
    write(1,buff,10);
    return 0;
}