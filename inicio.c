#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

#define TAMANHO_A 10000
#define NUM_THREADS 100
#define TAMANHO_BLOCO 100

int vetor_a[TAMANHO_A];

void inicializa_vetor_inteiro(int vetor[],int tam,int valor)
{
	for(int i = 0;i <= tam;i++)
		vetor[i] = valor;
}

void imprime_vetor(int vetor[],int tam)
{
	for(int i = 0;i <= tam;i++)
		if(i == 0 || i == tam)
			printf("Posição %d -- Valor %d\n",i,vetor[i]);
}

void somar(int vetor[],int id_thread)
{
	int inicio = id_thread * TAMANHO_BLOCO;
	int fim = inicio + TAMANHO_BLOCO;
	int soma = 0;
	
	printf("Somando o Trabalho da Thread --- %d \n",id_thread);
		
	for(int i = inicio; i <= fim; i++)
		soma += vetor[i];
		
	printf("Soma Finalizada da Thread %d --- %d\n",id_thread,soma);
}

void* rotina(void* args)
{
	void *aux = (void *) args;
	int thread_id = (int) aux;
	int inicio = thread_id * TAMANHO_BLOCO;
	int fim = inicio + TAMANHO_BLOCO;
	
	for(int i = inicio; i <= fim; i++)
	{
		vetor_a[i] = vetor_a[i] * 2;
	}
		
	printf("Terminei THREAD ID --- %d\n",thread_id);
	pthread_exit(NULL);
}

int main (void)
{
	pthread_t vetor_threads[NUM_THREADS];
	
	inicializa_vetor_inteiro(vetor_a,TAMANHO_A,5);
	imprime_vetor(vetor_a,TAMANHO_A);
	
	//Criar as Threads - NUM_THREADS
	for(int i = 0;i < NUM_THREADS; i++)
		pthread_create(&vetor_threads[i],NULL,rotina,(void *)i);
	
	for(int i = 0;i < NUM_THREADS; i++)
	{
		pthread_join(vetor_threads[i],NULL);
		somar(vetor_a,i);
	}
 
	imprime_vetor(vetor_a,TAMANHO_A);
	
	printf("Terminou a Execução\n");
	
}
