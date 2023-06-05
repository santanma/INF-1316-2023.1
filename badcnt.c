#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

//geeks for geeks ---- semaphores in process synchronization
//geeks for geeks ---- ipc shared memory

// xerxes shared memory
//hps.vi4io summer term shared memory
//http://www.csc.villanova.edu/~mdamian/threads/posixthreads.html
//https://cgi.di.uoa.gr/~ad/k22/k22-lab-notes4.pdf
//https://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/shm/shmat.html

#define NITER 1000000

int cnt = 0;
sem_t mutex;

void * Count(void * a)
{
    int i, tmp;
    void *aux = (void *) a;
    int id = (int) aux;
    
    for(i = 0; i < NITER; i++)
    {
    	sem_wait(&mutex);
    	if(cnt%100000==0) printf("Imprimir a Thread %d ---> %d\n",id,cnt);
        tmp = cnt;      /* copy the global cnt locally */
        tmp = tmp+1;    /* increment the local copy */
        cnt = tmp;      /* store the local value into the global cnt */ 
        //if(cnt > 100 && id == 1) return;
        sem_post(&mutex);
        
    }
}

int main(int argc, char * argv[])
{
    pthread_t tid1, tid2;
	sem_init(&mutex,0,1);
    if(pthread_create(&tid1, NULL, Count, 1))
    {
      printf("\n ERROR creating thread 1");
      exit(1);
    }

    if(pthread_create(&tid2, NULL, Count, 2))
    {
      printf("\n ERROR creating thread 2");
      exit(1);
    }

    if(pthread_join(tid1, NULL))	/* wait for the thread 1 to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }
    
    printf("Acabou 1\n");

    if(pthread_join(tid2, NULL))        /* wait for the thread 2 to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }
    
    printf("Acabou outro\n");

    if (cnt < 2 * NITER) 
        printf("\n BOOM! cnt is [%d], should be %d\n", cnt, 2*NITER);
    else
        printf("\n OK! cnt is [%d]\n", cnt);
  
  	sem_destroy(&mutex);
    pthread_exit(NULL);
}


