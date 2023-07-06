#include "lista.h"
#include "fila.h"

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>

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
	struct timeval tempoInicial;
	struct timeval tempoFinal;
	
	NoMemoria *proximo;
};
