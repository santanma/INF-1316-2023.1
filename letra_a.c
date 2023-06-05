#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define QTD_MENSAGENS 32
sem_t mutex;


int main (void)
{
	pid_t escritor;
	pid_t leitor;
	char buf[200];
	int *tamanho_fila; 
	
	sem_init(&mutex,0,1);
	
	key_t key = ftok("shmfile",65);
	
	int shmid = shmget(key,1024,0666|IPC_CREAT);
	int shmid_fila = shmget(IPC_PRIVATE,sizeof(int),0666|IPC_CREAT);
	
	tamanho_fila = (int *) shmat(shmid_fila,0,0);
	char *str = (char*) shmat (shmid,(void *)0,0);
	
	*tamanho_fila = 0;
			
	printf("Pai %d\n",getpid());
	
	if((leitor = fork()) > 0)
	{
		if((escritor = fork()) > 0) {}
		else
		{
			printf("Processo Escritor -- PID = %d\n",getpid());
			//printf("Escritor %d e Leitor %d dentro do Escritor\n",escritor,leitor);
			for(int i = 0; i < QTD_MENSAGENS ; i++)
			{
				sem_wait(&mutex);
				printf("Escrevendo Mensagem\n");
				//char *result = malloc(strlen("Mensagem de Número ") + strlen((char)i) + 1);
				//strcpy(result,"Mensagem de Número ");
				//strcat(result,(char)i);
			
				snprintf(buf,200,"Mensagem de Numero %d",i+1);	
				memcpy(str,buf,200);
				*tamanho_fila = 1;
				sem_post(&mutex);	
				while(*tamanho_fila == 1) {if(i == QTD_MENSAGENS-1) exit(0); }
			}
		}
	}
	else
	{
			printf("Processo Leitor -- PID = %d\n",getpid());
			//printf("Escritor %d e Leitor %d dentro do Leitor\n",escritor,leitor);
			for(int i = 0; i < QTD_MENSAGENS ; i++)
			{
				sem_wait(&mutex);
				if(*tamanho_fila == 1)
				{
					printf("Lendo Mensagem Recebida %s\n",str);
					*tamanho_fila = 0;
				}
				sem_post(&mutex);
				while(*tamanho_fila == 0) {if(i == QTD_MENSAGENS-1) exit(0);}
			}
	}
		
	for(int i = 0;i < 2; i++) wait(NULL);
	
	sem_destroy(&mutex);
	
	shmdt(str);
	shmdt(tamanho_fila);
	
	shmctl(shmid,IPC_RMID,NULL);
	shmctl(shmid_fila,IPC_RMID,NULL);
}
