//Pun programs seperately to get result

//execl
#include <unistd.h>
 
int main(void) {
  char *binaryPath = "/bin/ls";
  char *arg1 = "-lh";
  char *arg2 = "/home";
 
  execl(binaryPath, binaryPath, arg1, arg2, NULL);
 
  return 0;
}

//execlp
#include <unistd.h>
 
int main(void) {
  char *programName = "ls";
  char *arg1 = "-lh";
  char *arg2 = "/home";
 
  execlp(programName, programName, arg1, arg2, NULL);
 
  return 0;
}

//execv
#include <unistd.h>
 
int main(void) {
  char *binaryPath = "/bin/ls";
  char *args[] = {binaryPath, "-lh", "/home", NULL};
 
  execv(binaryPath, args);
 
  return 0;
}
//execvp
#include <unistd.h>
 
int main(void) {
  char *programName = "ls";
  char *args[] = {programName, "-lh", "/home", NULL};
 
  execvp(programName, args);
 
  return 0;
}

