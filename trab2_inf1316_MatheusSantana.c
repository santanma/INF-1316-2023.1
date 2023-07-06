/*Leitura de Arquivos - https://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

FILE *arquivoLog;

#define MAX_MENSAGEM_LOG 4096
#define MAX_LINHA_ARQUIVO 50

Fila *filaProntos;
Fila *filaBloqueados;

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
		
	arquivoProcessos = fopen(nomeArquivoProcesso,"r");
	
	if(arquivoProcessos == NULL)
	{
		printf("Erro na Abertura do Arquivo de Processos para Leitura\n");
		exit(0);
	}
	
	sprintf(mensagem,"Iniciando Leitura dos Processos ---> %s\n",nomeArquivoProcesso);
	fprintf(arquivoLog,mensagem);
	
	idLinha = 1;
	idProcesso = 0;
	
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
			idProcesso++;
			
			tamanhoProcesso = (int)(linha[strlen(linha)-4]) - '0';
		
			fprintf(arquivoLog,"Lendo Processo Nº %d - Tamanho %d\n",idProcesso,tamanhoProcesso);
			
			inserirFila(filaProntos,idProcesso,tamanhoProcesso,0,"",0);
			continue;
		}
		else if(strstr(linha,"exec") || strstr(linha,"io"))
		{
			
		}
		else
		{
			quantidadeExecIo = atoi(linha);
			
		
		}
		
		
		
	}
}

int main ()
{
	inicializarArquivoLog("log_SimuladorMemoria.txt");
	inicializarFilas("Processo.txt");
}
