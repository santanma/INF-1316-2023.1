/*******************************************Identificação***************************************************
Matheus Santana da Silva 2021087

Enunciado
Item 1a
Processos Síncronos
* Processo 1 Escreve Mensagem na Memória Compartilhada
* Processo 2 Lê a Mensagem da Memória Compartilhada
* Processo 2 Informa ao Processo 1 que este pode enviar uma Nova Mensagem

Obs.: Não pode ser utilizado um Buffer para Armazenamento das Mensagens
*******************************************/

/*******************************************Estrutura do Programa*******************************************
*/


/********************************************Solução - Código Fonte, Saída e Comentários********************

O Enunciado pede para usarmos a Memória Compartilhada como IPC e os Semáforos para a Sincronização entre os Processos 
que devem ser Independentes. 
Uma forma possível é criar Dois Processos com o mesmo pai, sendo um com o Papel de Escritor e o outro com o Papel de Leitor.
Para Implementação começamos criando e anexando as variáveis à Memória Compartilhada, que será nesse caso uma String[Mensagem de Texto]
Em seguida será necessário alocar espapço para o Semáforo, com uma Observação de que ele também precisará estar na Memória Compartilhada,
do contrário os Processos não conseguirão cooperar entre si da maneira esperada. Utilizarei a API POSIX para Semáforos para a Implementação

Referência.: https://docs.oracle.com/cd/E19048-01/chorus5/806-6897/architecture-7/index.html

Para que a Implementação funcione é necessário utilizar uma estratégia de Implementação que Envolve um Mutex e dois semáforos contadores

Mutex -> Controlar a Entrada na Região Crítica para Escrita da Mensagem
Full -> Indica quantos Slots foram preenchidos. Nesse Exercício não temos uma Fila de Mensagens.Logo, ficará entre 0 e 1
Empty -> Indica quantos Slots ainda podem ser preenchidos. 

== O Processo Escritor para mandar uma mensagem precisa
1 - Decrementar Empty
2 - Entrar na Região Crítica Travando o Mutex
3 - Escrever a Mensagem
4 - Sair da Região Crítica Destravando o Mutex
5 - Incrementar Full

 == O Processo Leitpr para ler uma mensagem precisa
1 - Decrementar Full
2 - Entrar na Região Crítica Travando o Mutex
3 - Ler a Mensagem
4 - Sair da Região Crítica Destravando o Mutex
5 - Incrementar Empty


Referência.: https://www.geeksforgeeks.org/producer-consumer-problem-using-semaphores-set-1/

Outras Referências Utilizadas
* https://www.youtube.com/watch?v=WgVSq-sgHOc
* https://stackoverflow.com/questions/16400820/how-to-use-posix-semaphores-on-forked-processes-in-c
* https://www.youtube.com/watch?v=4MHFIROTXlc

*/
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

#define BLOCK_SIZE 4096
#define IPC_RESULT_ERROR -1
#define NUM_PROCESSOS 2
#define NUM_MENSAGENS 32


void unlink_all_semaphores()
{
	sem_unlink("mutex");
	sem_unlink("empty");
	sem_unlink("full");
}

void handle_sigint(int sig)
{
	unlink_all_semaphores();
	abort();
}

int main (void)
{
	key_t mem_key;
	int shm_id;
	char buf[BLOCK_SIZE];
	char *mensagem;
	
	sem_t *mutex;
	sem_t *full;
	sem_t *empty;
	
	pid_t escritor;
	pid_t leitor;
	
	/*Alocar Memória Compartilhada*/
	mem_key = ftok("item_a",'a');
	shm_id = shmget(mem_key,BLOCK_SIZE,IPC_CREAT | 0666);
	if(shm_id < 0) 
	{
		printf("Erro na Alocação da Memória Compartilhada\n");
		exit(1);
	}
	
	mensagem = (char *) shmat (shm_id,NULL,0);
	if((mensagem == (char *)IPC_RESULT_ERROR))
	{
		printf("Erro ao Conectar Variável 'Mensagem' na Memória\n");
		exit(1);
	}
	
	/*Inicializar Semáforo*/
	
	signal(SIGINT,handle_sigint);
	
	mutex = sem_open("mutex",O_CREAT | O_EXCL, 0644, 1);
	if(mutex == NULL) 
	{
		printf("Semáforo MUTEX já estava criado. Reinicie o Programa \n");
		unlink_all_semaphores();
		abort();
	}
		
	full = sem_open("full",O_CREAT | O_EXCL, 0644, 0);
	if(full == NULL) 
	{
		printf("Semáforo FULL já estava criado. Reinicie o Programa \n");
		unlink_all_semaphores();
		abort();
	}
	
	empty = sem_open("empty",O_CREAT | O_EXCL, 0644, 1);
	if(empty == NULL) 
	{
		printf("Mutex já estava criado. Reinicie o Programa \n");
		unlink_all_semaphores();
		abort();
	}	
	
	//Processo do Escritor e Leitor
	if((leitor = fork()) > 0)
	{
		if((escritor = fork()) > 0) {} 
		else
		{
			for(int i = 0; i < NUM_MENSAGENS ; i++)
			{
				sem_wait(empty);
				sem_wait(mutex);
				printf("%d - Digite a Mensagem que Deseja Enviar:",i+1);
				fgets(buf,BLOCK_SIZE,stdin);
				memcpy(mensagem,buf,BLOCK_SIZE);	
				sem_post(mutex);
				sem_post(full);
			}
		}
	}
	else 
	{
		for(int i = 0; i < NUM_MENSAGENS ; i++)
		{
				sem_wait(full);
				sem_wait(mutex);
				printf("Mensagem Recebida .:%s",mensagem);
				sem_post(mutex);
				sem_post(empty);
		}
	}
	
	for(int j = 0;j < NUM_PROCESSOS; j++) wait(NULL);
	
	/*Desalocar Memória Compartilhada*/
	shmdt(mensagem);
	shmctl(shm_id,IPC_RMID,NULL);
	
	/*Desalocar Semáforo*/
	sem_unlink("mutex");
	sem_close(mutex);
	
	sem_unlink("full");
	sem_close(full);
	
	sem_unlink("empty");
	sem_close(empty);
	exit(0);
}

/*******************************************Saída do Programa********************************************
Compilar $ gcc -Wall -o item_a item_a.c
Executar $./item_a

1 - Digite a Mensagem que Deseja Enviar:Vou Recitar um Poema.
Mensagem Recebida .:Vou Recitar um Poema.
2 - Digite a Mensagem que Deseja Enviar:Em 30 Mensagens
Mensagem Recebida .:Em 30 Mensagens
3 - Digite a Mensagem que Deseja Enviar:Quando nasci, um anjo torto
Mensagem Recebida .:Quando nasci, um anjo torto
4 - Digite a Mensagem que Deseja Enviar: desses que vivem na sombra
Mensagem Recebida .: desses que vivem na sombra
5 - Digite a Mensagem que Deseja Enviar: disse: Vai, Carlos! ser gauche na vida.
Mensagem Recebida .: disse: Vai, Carlos! ser gauche na vida.
6 - Digite a Mensagem que Deseja Enviar:As casas espiam os homens
Mensagem Recebida .:As casas espiam os homens
7 - Digite a Mensagem que Deseja Enviar: que correm atrás de mulheres.
Mensagem Recebida .: que correm atrás de mulheres.
8 - Digite a Mensagem que Deseja Enviar: A tarde talvez fosse azul,
Mensagem Recebida .: A tarde talvez fosse azul,
9 - Digite a Mensagem que Deseja Enviar: não houvesse tantos desejos.
Mensagem Recebida .: não houvesse tantos desejos.
10 - Digite a Mensagem que Deseja Enviar:O bonde passa cheio de pernas:
Mensagem Recebida .:O bonde passa cheio de pernas:
11 - Digite a Mensagem que Deseja Enviar: pernas brancas pretas amarelas.
Mensagem Recebida .: pernas brancas pretas amarelas.
12 - Digite a Mensagem que Deseja Enviar: Para que tanta perna, meu Deus, pergunta meu coração.
Mensagem Recebida .: Para que tanta perna, meu Deus, pergunta meu coração.
13 - Digite a Mensagem que Deseja Enviar: Porém meus olhos
Mensagem Recebida .: Porém meus olhos
14 - Digite a Mensagem que Deseja Enviar: não perguntam nada.
Mensagem Recebida .: não perguntam nada.
15 - Digite a Mensagem que Deseja Enviar:O homem atrás do bigode
Mensagem Recebida .:O homem atrás do bigode
16 - Digite a Mensagem que Deseja Enviar: é sério, simples e forte.
Mensagem Recebida .: é sério, simples e forte.
17 - Digite a Mensagem que Deseja Enviar: Quase não conversa.
Mensagem Recebida .: Quase não conversa.
18 - Digite a Mensagem que Deseja Enviar: Tem poucos, raros amigos
Mensagem Recebida .: Tem poucos, raros amigos
19 - Digite a Mensagem que Deseja Enviar: o homem atrás dos óculos e do bigode,
Mensagem Recebida .: o homem atrás dos óculos e do bigode,
20 - Digite a Mensagem que Deseja Enviar:Meu Deus, por que me abandonaste
Mensagem Recebida .:Meu Deus, por que me abandonaste
21 - Digite a Mensagem que Deseja Enviar: se sabias que eu não era Deus
Mensagem Recebida .: se sabias que eu não era Deus
22 - Digite a Mensagem que Deseja Enviar: se sabias que eu era fraco.
Mensagem Recebida .: se sabias que eu era fraco.
23 - Digite a Mensagem que Deseja Enviar:Mundo mundo vasto mundo,
Mensagem Recebida .:Mundo mundo vasto mundo,
24 - Digite a Mensagem que Deseja Enviar: se eu me chamasse Raimundo
Mensagem Recebida .: se eu me chamasse Raimundo
25 - Digite a Mensagem que Deseja Enviar: seria uma rima, não seria uma solução.
Mensagem Recebida .: seria uma rima, não seria uma solução.
26 - Digite a Mensagem que Deseja Enviar: Mundo mundo vasto mundo,
Mensagem Recebida .: Mundo mundo vasto mundo,
27 - Digite a Mensagem que Deseja Enviar: mais vasto é meu coração.
Mensagem Recebida .: mais vasto é meu coração.
28 - Digite a Mensagem que Deseja Enviar:Eu não devia te dizer
Mensagem Recebida .:Eu não devia te dizer
29 - Digite a Mensagem que Deseja Enviar: mas essa lua
Mensagem Recebida .: mas essa lua
30 - Digite a Mensagem que Deseja Enviar: mas esse conhaque
Mensagem Recebida .: mas esse conhaque
31 - Digite a Mensagem que Deseja Enviar: botam a gente comovido como o diabo.
Mensagem Recebida .: botam a gente comovido como o diabo.
32 - Digite a Mensagem que Deseja Enviar:Fim do Poema
Mensagem Recebida .:Fim do Poema

Destaques da Implementação
=> Para trabalhar com Semáforos e Processos é necessário lembrar que eles devem ser inicializados antes do Fork()
e também precisam ser colocados na memória compartilhada, do contrário as alterações que um Processo executar 
nos Semáforos não serão vistas pelo outro processo.
=> Ao invés de utilizar scanf() para leitura da mensagem do teclado utilizer fgets() para conseguir ler a mensagem
com espaços
=> Sem_open() é melhor para trabalhar com processos do que sem_init() pois facilita a forma de implementar a alocação 
do semáforo na memória compartilhada
=> Percebi que ao usar semáforos com nome existe um problema que precisa ser tratado que é ter cuidado para garantir 
sempre a adequada finalização dos semáforos. Para sempre garantir o comportamento esperado coloquei alguns tratamentos
no código, verificando os semáforos após uma tentativa de criação. Além disso, durante os testes utilizei o SINAL
CTRL + C do teclado que fez com que os programas seguintes tivessem problemas para executar pois os semáforos não foram
fechados adequadamente. Portanto, coloquei um Signal Handler para esse caso em específico para limpar os semáforos todos
caso o usuário aperte CTRL + C. Isso reduz a chance de algum problema de inicialização de Semáforos na próxima execução
do programa.

*/
/*******************************************Testes e Conclusões******************************************
Para Validar a Implementação fiz testes com diferentes Tamanhos de Mensagens
Coloquei frases inteiras e palavras soltas. 
A sincronização funcionou adequadamente até o final do total de execuções, determinados pela variável NUM_MENSAGENS

*/
