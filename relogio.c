/*https://stackoverflow.com/questions/38831057/how-to-measure-the-execution-time-in-micro-seconds */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main ()
{
	struct timeval st, et;

	gettimeofday(&st,NULL);

	sleep(4);

	gettimeofday(&et,NULL);

	int elapsed = (et.tv_sec - st.tv_sec);

	printf("Tempo Decorrido: %d\n",elapsed);

}
