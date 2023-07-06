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
	TipoInformacao *tipoInformacao;
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
		if(ptr->idProcesso == idProcesso) {} //Update
		ptr = ptr->proximo;		 	
	}
	
	if(!encontrado)
	{
		NoProcesso *processo = (NoProcesso*) malloc (sizeof(NoProcesso));
		processo->idProcesso = idProcesso;
		processo->tamanhoProcesso = tamanhoProcesso;
		processo->quantidadeExecIo = quantidadeExecIo;
				
		if(!strcmp(tipoExecIo,""))
		{
			printf("esta vazio\n");
		
		}
		
		processo->proximo = NULL;
		
		if(f->fim != NULL)
			f->fim->proximo = processo;
		else
			f->inicio = processo;
			
		f->fim = processo;
	}

}
