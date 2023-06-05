#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

//codequoi - Creating and Killing Child Process

int main (void)
{
	pid_t pid_chamador = fork();
	
	if(pid_chamador > 0)
	 	pid_t pid_atendente = fork();
	
}
