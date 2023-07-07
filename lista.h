#include <stdbool.h>
#include "fila.h"

typedef struct lista Lista;
typedef struct noMemoria NoMemoria;

Lista* criarListaCPU(int tamanhoCPU);

bool listaCPUVazia(Lista *listaCPU);

NoMemoria* localizarParticaoExecutandoNaCPU(Lista *listaCPU);

void insereListaCPUOrdenada(Lista *listaCPU,NoMemoria *particaoNova,NoMemoria *particaoCorrente);

void alocarMemoriaBestFit(Lista *listaCPU,NoProcesso *processo);

