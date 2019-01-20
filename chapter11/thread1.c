#include "apue.h"
#include <pthread.h>

pthread_t ntid;


int a = 3;

void *thr_fn (void *arg)
{
	printf ("new thread a = %d\n", a++);
}

int main (void)
{
	int err;
	err = pthread_create (&ntid, NULL, thr_fn, NULL);

	//sleep (1);
	printf ("main process a = %d\n", a++);
	exit (0);
}
