#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    if (fork() || fork())    
        fork();
 
    printf("1 ");
    printf("Id do Pai %d",getppid());
    while (wait(NULL) > 0); // this way, the father waits for all the child processes 
    return 0;
}
