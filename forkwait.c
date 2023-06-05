#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/*O que o Código está ensinando
1 - Criar um Processo Filho
2 - Diferenciar Processo Filho do Processo Pai pelo Id
3 - Imprimir os Ids do Processo Corrente e de seu Pai
4 - Usar a Função Wait para aguardar o Filho terminar
5 - Verificar que sem a Função Wait() o getppid() pode não funcionar conforme o esperado
6 - Verificar o Retorno da Função Wait() que é o Pid do Filho que terminou
*/

int main (void)
{
	pid_t pid;
	pid_t id_wait;
	pid = fork();
	printf("Valor Retornado %d \n",pid);
	
	if(pid == 0) { /*Child Process*/
		printf("Executa Filho - Meu Id %d\n",getpid());
		printf("Executa Filho - Id Pai %d\n",getppid());
	}
	else {
		printf("Executa Pai - Meu Id %d\n",getpid()); /*Parent Process*/
		printf("Executa Pai - Id Pai %d\n",getppid()); 
	}
	id_wait = wait(NULL);
	printf("Terminou o Processo %d ----> Executando %d\n",id_wait,getpid());
}
