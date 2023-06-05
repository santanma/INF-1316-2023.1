#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	
	if((pid = fork()) > 0) {
		printf("Quem acabou -- >%d\n",wait(NULL));
		char *args[]={"./meuecho","Executando Processo Pai"};
		printf("Fork Pid %d\n",pid);
		execvp(args[0],args);	
		printf("Não vai Exibir");		
	}
	
    printf("Terminando a Chamada de Quem Mandou Executar\n");
}
