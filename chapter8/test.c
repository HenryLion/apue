#include "apue.h"

int main (void)
{
	pid_t pid;
	printf ("father pid = %d\n", getpid());
	if ((pid = fork ()) < 0)
		err_sys ("fork error");
	else if (pid == 0)
	{
		sleep (3);
		printf ("son pid = %d\n", getpid());
	}

	printf ("hello, world %d\n", getpid());

	return 0;
}
