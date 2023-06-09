#include "fila.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct tipoInformacao {
	char tipoExecIo[5]; /*exec ou Io*/
	int tempoExecIo; 
};

struct noProcesso {
	int idProcesso;
	int tamanhoProcesso; /*Pela Especificação pode ser de 2Kb,3Kb,4Kb ... ou 8Kb*/
	int quantidadeExecIo;
	int quantidadeExecIoLidas; /*Auxiliar para Contarmos quantas Ops de Exec/Io 
								já foram inseridas a partir do arquivo de Processos
								Importante apenas na Inicialização*/
	TipoInformacao *tipoInformacao;
	
	struct timeval tempoInicialProcesso;
	struct timeval tempoFinalProcesso;
	
	NoProcesso *proximo;
};

struct fila {
	NoProcesso *inicio;
	NoProcesso *fim;
};

Fila* criarFila ()
{
	Fila *f = (Fila *) malloc(sizeof(Fila));
	f->inicio = f->fim = NULL;

	return f;
}

void inserirFila (Fila *f,
				  int idProcesso,
				  int tamanhoProcesso,
				  int quantidadeExecIo,
				  char *tipoExecIo,
				  int tempoExecIo)
{
	//Estratégia.: Implementar um Insert ou Update
	//Se Encontrar o IdProcesso = Insert
	//Caso contrário            = Update
	//Percorrer a Fila definirá o Tipo da Operação
	NoProcesso *ptr = f->inicio;
	bool encontrado = false;
	
	while(ptr!=NULL)
	{
		if(ptr->idProcesso == idProcesso) // Update
		{ 
			encontrado = true;
			
			ptr->quantidadeExecIo = quantidadeExecIo;
		
			if(ptr->tipoInformacao == NULL) 
			{
				ptr->tipoInformacao = (TipoInformacao*) malloc 	(sizeof(TipoInformacao)*quantidadeExecIo);	
			}	
				
			if(tipoExecIo[0] != '\0')
			{
				TipoInformacao informacaoExecIo;
			 	strcpy(informacaoExecIo.tipoExecIo,tipoExecIo);
			 	informacaoExecIo.tempoExecIo = tempoExecIo;
			 	
			 	ptr->tipoInformacao[ptr->quantidadeExecIoLidas] = informacaoExecIo;
			 	
			 	ptr->quantidadeExecIoLidas++;
			}
			break;
		} 
		
		ptr = ptr->proximo;		 	
	}
	
	if(!encontrado)
	{
		NoProcesso *processo = (NoProcesso*) malloc (sizeof(NoProcesso));
		processo->idProcesso = idProcesso;
		processo->tamanhoProcesso = tamanhoProcesso;
		processo->quantidadeExecIoLidas = 0;
		
		processo->proximo = NULL;
		
		if(f->fim != NULL)
			f->fim->proximo = processo;
		else
			f->inicio = processo;
			
		f->fim = processo;
	}

}


void imprimirFila(Fila *f)
{
	NoProcesso *ptr = f->inicio;
	
	for(;ptr!=NULL;ptr = ptr->proximo)
	{
		printf("Id Processo %d - ",ptr->idProcesso);
		printf("Tamanho Processo %d Kb - ",ptr->tamanhoProcesso);
		printf("Quantidade Exec/Io %d",ptr->quantidadeExecIo);
		
		printf("\n{");
		for(int i = 0;i < ptr->quantidadeExecIoLidas; i++)
		{
			printf("[%s:%d] ",ptr->tipoInformacao->tipoExecIo,ptr->tipoInformacao[i].tempoExecIo);	
		}
		printf("}\n");
	}

}

bool filaVazia(Fila *f)
{
	return (f->inicio == NULL);
}

NoProcesso* retirarProcessoDaFila(Fila *f)
{
	if(!filaVazia(f)) //Valida se de Fato tem o que tirar para não usar ponteiros inadequadamente
	{ 
		NoProcesso *retorno = f->inicio;
		f->inicio = retorno->proximo;

		if(f->inicio == NULL)
			f->fim = NULL;

		retorno->proximo = NULL; //Solta da Fila
			
		return retorno;
	}	

	return NULL;
}

int pegarTamanhoProcesso (NoProcesso *processo)
{
	return processo->tamanhoProcesso;
}

int pegarIdProcesso (NoProcesso *processo)
{
	return processo->idProcesso;
}
