/*Leitura de Arquivos - https://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm 
https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "fila.h"
#include "lista.h"

FILE *arquivoLog;

#define MAX_MENSAGEM_LOG 4096
#define MAX_LINHA_ARQUIVO 50

Fila *filaProntos;
Fila *filaBloqueados;
Lista *listaCPU;

void inicializarArquivoLog (char *nomeArquivoLog);
void inicializarFilas (char *nomeArquivoProcesso);
void iniciarProcessamentoCPU();

void inicializarArquivoLog (char *nomeArquivoLog)
{
	char mensagem[MAX_MENSAGEM_LOG];

	arquivoLog = fopen(nomeArquivoLog,"w");
	
	if(arquivoLog == NULL)
	{
		printf("Erro na Abertura do Arquivo de Log para Escrita\n");
		exit(0);
	}
	
	sprintf(mensagem,"Arquivo de Log Criado com Sucesso ---> %s\n",nomeArquivoLog);
	fprintf(arquivoLog,mensagem);
}

void inicializarFilas (char *nomeArquivoProcesso)
{
	FILE *arquivoProcessos;
	char mensagem[MAX_MENSAGEM_LOG]; 
	char linha[MAX_LINHA_ARQUIVO];
	int idLinha;
	int quantidadeProcessos;
	int idProcesso;
	int tamanhoProcesso;
	int quantidadeExecIo;
	char tipoExecIo[5];
	int tempoExecIo;
		
	arquivoProcessos = fopen(nomeArquivoProcesso,"r");
	
	if(arquivoProcessos == NULL)
	{
		printf("Erro na Abertura do Arquivo de Processos para Leitura\n");
		exit(0);
	}
	
	sprintf(mensagem,"Iniciando Leitura dos Processos ---> %s\n",nomeArquivoProcesso);
	fprintf(arquivoLog,mensagem);
	
	idLinha = 1;
	
	while(fgets(linha,MAX_LINHA_ARQUIVO,arquivoProcessos) != NULL)
	{
		if(idLinha == 1)
		{
			quantidadeProcessos = atoi(linha);
			
			sprintf(mensagem,"Quantidade de Processos ---> %d\n",quantidadeProcessos);
			fprintf(arquivoLog,mensagem);
	
			filaProntos = criarFila();
			filaBloqueados = criarFila();	
				
			idLinha++;
		}
		else if(strstr(linha,"Processo"))
		{
			tamanhoProcesso = (int)(linha[strlen(linha)-4]) - '0';
		
			char *token = strtok(linha," ");
			
			while(token != NULL)
			{
				//Pegar o Id Do Processo de Forma Dinâmica
				if(token[0] == '#') 
				{
					idProcesso = atoi(strtok(token,"#"));
				}			
				
				token = strtok(NULL," ");
			}
		
			fprintf(arquivoLog,"Lendo Processo Nº %d - Tamanho %d\n",idProcesso,tamanhoProcesso);
			
			inserirFila(filaProntos,idProcesso,tamanhoProcesso,0,"",0);
			continue;
		}
		else if(strstr(linha,"exec") || strstr(linha,"io"))
		{
			char *token = strtok(linha," ");
			int index = 1;
			
			//Pegar Exec/Io e seu tempo
			while (token != NULL)
    		{
    			if(index == 1)
    			{
    				strcpy(tipoExecIo,token);
    				index++;
    			}
    			else
    			{
    				tempoExecIo = atoi(token);    			
    			}
       		 	token = strtok(NULL, " ");
    		}
					inserirFila(filaProntos,idProcesso,tamanhoProcesso,quantidadeExecIo,tipoExecIo,tempoExecIo);	
					
			//printf("*****Nova Execução*****\n");
			//imprimirFila(filaProntos);				
		}
		else
		{
			quantidadeExecIo = atoi(linha);
			inserirFila(filaProntos,idProcesso,tamanhoProcesso,quantidadeExecIo,"",0);		
		}
	}
}

void iniciarProcessamentoCPU() 
{
	struct timeval tempoInicialRelogio;
	struct timeval tempoFinalRelogio;
	
	int tempoDecorrido;
	
	char tipoAlgoritmo;

	fprintf(arquivoLog,"Iniciando CPU - Relógio será Disparado\n");
	fprintf(arquivoLog,"Inicializando Lista de Memória da CPU\n");
	
	fprintf(arquivoLog,"Capturando o Algoritmo de Alocação de Memória\n");
	
	printf("Escolha o Algoritmo de Alocação de Memória a ser Adotado:\n");
	printf("F - First Fit\n");
	printf("B - Best Fit\n");
	printf("W - Worst Fit\n");
	
	scanf("&c ",&tipoAlgoritmo);
	
	gettimeofday(&tempoInicialRelogio,NULL);
	
	listaCPU = criarLista();

	while(!filaVazia(filaProntos) && !filaVazia(filaBloqueados) && !listaVazia(listaCPU))
	{
		gettimeofday(&tempoFinalRelogio,NULL);
	
		tempoDecorrido = (tempoFinalRelogio.tv_sec - tempoInicialRelogio.tv_sec);
	
		if(tempoDecorrido%1 == 0 || tempoDecorrido < 1) //Contemplar o Início do Programa
		{		
			//Passo 1 - Verificar os Prontos
			NoProcesso *processo = retirarProcessoDaFila(filaProntos);
		
			switch(tipoAlgoritmo)
			{ 
				case 'F':
					printf("Escolheu First Fit\n");
				case 'B':
					printf("Escolheu Best Fit\n");
				case 'W':
					printf("Escolheu Worst Fit\n");			
			}	 
		
			//Passo 2 - Verificar os Bloqueados
			retirarProcessoDaFila(filaBloqueados);
		
			//Passo 3 - Verificar quem está na CPU
			
			
			sleep(1);
		}		
	}
	
	printf("Fila Prontos Vazia \n");
	printf("Fila Bloqueados Vazia \n");
	printf("Lista CPU Vazia \n");
}

int main ()
{
	inicializarArquivoLog("log_SimuladorMemoria.txt");
	inicializarFilas("Processo.txt");
	iniciarProcessamentoCPU();
}
