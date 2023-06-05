#include <stdio.h>
#include <signal.h>
#include <unistd.h>
 
//https://eric-lo.gitbook.io
//https://www-uxsup.csx.cam.ac.uk/courses/moved.Building/signals.pdf

int z;
int count = 0;
int f(int x, int y)
{
 int tmp = x + y;
 z = tmp * 2 + 1;
 return z;
}

void handle_signal(int sig)
{
 int t = f(4,5);
 printf("%d\n",t); 
 count++;
 return;
}

int main()
{
 signal(SIGINT,handle_signal);
 int v = f(1,2);
 printf("%d\n",v);
 raise(SIGINT);
 //while(count < 4);
}
