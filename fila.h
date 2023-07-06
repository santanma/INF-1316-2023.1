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
