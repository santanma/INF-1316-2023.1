#include <stdbool.h> 

typedef struct tipoInformacao TipoInformacao;
typedef struct noProcesso NoProcesso;
typedef struct fila Fila;

Fila* criarFila ();

void inserirFila (Fila *f,
				  int idProcesso,
				  int tamanhoProcesso,
				  int quantidadeExecIo,
				  char *tipoExecIo,
				  int tempoExecIo);

void imprimirFila(Fila *f);
 
bool filaVazia(Fila *f);

NoProcesso* retirarProcessoDaFila(Fila *f);

int pegarTamanhoProcesso (NoProcesso *processo);

int pegarIdProcesso (NoProcesso *processo);
