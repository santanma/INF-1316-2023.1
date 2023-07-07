#include "lista.h"
#include "fila.h"

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

struct lista
{
	NoMemoria *inicio;
};

struct noMemoria
{
	int enderecoInicial;
	int tamanhoParticao;
	bool preenchido;
	
	NoProcesso *processo; /*Informações do Processo em Execução*/		
	NoMemoria *proximo;
};

Lista* criarLista()
{
	Lista *l = (Lista *) malloc(sizeof(Lista));
	l->inicio = NULL;

	return l;
}

bool listaVazia(Lista *l)
{
	return (l->inicio == NULL);
}
