/*https://stackoverflow.com/questions/38831057/how-to-measure-the-execution-time-in-micro-seconds */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main ()
{
	struct timeval st, et;
	int elapsed;

	gettimeofday(&st,NULL);
  
	while(elapsed <= 20)
	{
		gettimeofday(&et,NULL);

		elapsed = (et.tv_sec - st.tv_sec);
		if(elapsed%1 == 0)
		{
			printf("Tempo Decorrido: %d\n",elapsed);
			sleep(1);
		}
	}
}
