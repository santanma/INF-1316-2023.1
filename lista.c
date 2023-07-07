#include "lista.h"
#include "fila.h"

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

struct lista
{
	NoMemoria *inicio;
	int tamanhoCPU;
};

struct noMemoria
{
	int enderecoInicial;
	int tamanhoParticao;
	bool preenchido;
	
	NoProcesso *processo; /*Informações do Processo em Execução*/		
	NoMemoria *proximo;
};

Lista* criarListaCPU(int tamanhoCPU)
{
	Lista *listaCPU = (Lista *) malloc(sizeof(Lista));
	NoMemoria *memoria = (NoMemoria *) malloc (sizeof(NoMemoria));

	memoria->enderecoInicial = 0;
	memoria->tamanhoParticao = tamanhoCPU; /**Maximo Implementado sem as Partições conforme permitido no enunciado*/

	memoria->preenchido = false;

	listaCPU->inicio = memoria;
	listaCPU->tamanhoCPU = tamanhoCPU;

	return listaCPU;
}

bool listaCPUVazia(Lista *listaCPU)
{
	//*Conceito -> vazia se não houver ninguém na CPU Executando
	NoMemoria *ptr = listaCPU->inicio;

	for(;ptr!=NULL;ptr = ptr->proximo)
	{
		if(ptr->preenchido)
			return false;
	}
	return true;
}

NoMemoria* localizarParticaoExecutandoNaCPU(Lista *listaCPU)
{
	NoMemoria *ptr = listaCPU->inicio;

	for(;ptr!=NULL;ptr = ptr->proximo)
	{
		if(ptr->preenchido) // Pela Especificação Apenas UM Prcesso ocupa a CPU
			return ptr;
	}

	return NULL;
}

void insereListaCPUOrdenada(Lista *listaCPU,NoMemoria *particaoNova,NoMemoria *particaoCorrente)
{
	if(particaoCorrente == NULL)
	{
		listaCPU->inicio = particaoNova;

		NoMemoria *particaoVazia = (NoMemoria *) malloc (sizeof(NoMemoria));

		particaoVazia->enderecoInicial = particaoNova->tamanhoParticao;
		particaoVazia->tamanhoParticao = listaCPU->tamanhoCPU - particaoVazia->enderecoInicial;
		particaoVazia->preenchido = false;

		particaoNova->proximo = particaoVazia;
	}
	else
	{
		
	}

}

//Os Algoritmos BestFit,FirstFit e WorstFit consideram que o Processo que está na CPU
//no moment (Caso Exista) ja atingiu seu tempo Limite
//Essa verificação é feita previamente na Etapa Anterior pelo Relógio
void alocarMemoriaBestFit(Lista *listaCPU,NoProcesso *processo)
{
	NoMemoria *ptr = listaCPU->inicio;
	NoMemoria *menorParticao = NULL;

	int menorEspaco = listaCPU->tamanhoCPU + 1; //Força que Qualquer valor ganhe na comparação
	
	bool alocavel = false;

	for(;ptr!=NULL;ptr = ptr->proximo)
	{
		if(!(ptr->preenchido)
			&& ptr->tamanhoParticao < menorEspaco
			&& ptr->tamanhoParticao >= pegarTamanhoProcesso(processo))
		{
			menorEspaco = ptr->tamanhoParticao;
			menorParticao = ptr;
			alocavel = true;
		}
	}

	if(alocavel)
	{
		NoMemoria *particaoCorrente = localizarParticaoExecutandoNaCPU(listaCPU); 

		if(particaoCorrente != NULL)
		{
			//Retira o Processo que está na CPU

		}
		else // Nesse Caso, não havia ninguém na CPU
		{
			menorParticao->tamanhoParticao = pegarTamanhoProcesso(processo);
			menorParticao->preenchido = true;
			menorParticao->processo = processo;

			//Inserir na Lista Mantendo a Ordenação
			insereListaCPUOrdenada(listaCPU,menorParticao,particaoCorrente);
		}
	}
}
