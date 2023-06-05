#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/*O que o Código está ensinando
1 - Uma Variável alterada dentro do Processo Filho não é Alterada dentro do Processo Pai
2 - Processo pai Executa primeiro transformando a Variável em 11, mas seu filho ainda está lendo o valor 10
*/

int main (void)
{
	pid_t pid;
	int id_wait;
	int n = 10;
	pid = fork();
	printf("Valor Retornado %d \n",pid);
	
	if(pid == 0) { /*Child Process*/
		n = n + 100;
		printf("Processo Filho, Pid %d, n = %d\n",getpid(),n);
	}
	else {
	    n++;
	    printf("Processo Pai, Pid %d, n = %d\n",getpid(),n); /*Parent Process*/	 
	}
	id_wait = wait(NULL);
	printf("Terminou o Processo %d ----> Executando %d\n",id_wait,getpid());
}
