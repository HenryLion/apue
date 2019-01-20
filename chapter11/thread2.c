#include "apue.h"
#include <pthread.h>

#define THREAD_LOOP_TIME 20 
#define ARR_NUM 20 
int arr[ARR_NUM] = { 0 }; 
pthread_mutex_t my_first_lock;
void *fn1 (void *arg)
{
	int i = 0;
	for (; i < THREAD_LOOP_TIME; ++i)
	{
		pthread_mutex_lock (&my_first_lock);
		int j = 0;
		for (; j < ARR_NUM; ++j)
		{
			if (arr[j] == 0)
			{
				arr[j] += 5;
				arr[j] -= 4;
				arr[j] *= 34;
				arr[j] /= 34;
				printf ("thread 1 here add pos = %d\n", j);
				break;
			}
		}
		pthread_mutex_unlock (&my_first_lock);
	}
	return NULL;
}
void *fn2 (void *arg)
{
	int i = 0;
	for (; i < THREAD_LOOP_TIME; ++i)
	{

		pthread_mutex_lock (&my_first_lock);
		int j = 0;
		for (; j < ARR_NUM; ++j)
		{
			if (arr[j] == 0)
			{
				arr[j] += 5;
				arr[j] -= 4;
				arr[j] *= 34;
				arr[j] /= 34;
				printf ("thread 2 here add pos = %d\n", j);
				break;
			}
		}
		pthread_mutex_unlock (&my_first_lock);
	}
	return NULL;
}

void printarr ()
{
	int i = 0;
	for (; i < ARR_NUM; ++i)
	{
		if (1 != arr[i])
		 printf ("pos %d not equle 1, value is %d \n",i, arr[i]);
	}
}

int main (void)
{
	pthread_mutex_init (&my_first_lock, NULL);
	pthread_t tid1, tid2;
	pthread_create (&tid1, NULL, fn1, NULL);
	pthread_create (&tid2, NULL, fn2, NULL);

	sleep(1);

	printarr ();
	return 0;
}
