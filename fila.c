#include "fila.h"

#include <stdlib.h>
#include <stdio.h>

struct tipoInformacao {
	char tipoExecIo[5]; /*exec ou Io*/
	int tempoExecIo;	
};

struct noProcesso {
	int idProcesso;
	int tamanhoProcesso; /*Pela Especificação pode ser de 2Kb,3Kb,4Kb ... ou 8Kb*/
	int quantidadeExecIo;
	TipoInformacao tipoInformacao;
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


}
