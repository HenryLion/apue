#include "apue.h"
#include <sys/wait.h>

int main (void)
{
	pid_t pid;
	printf ("grandfather pid = %d\n", getpid());
	if ((pid = fork ()) < 0)
		err_sys ("fork error");
	else if (pid == 0)
	{
		printf ("first son pid = %d\n", getpid());
		if ((pid = fork ()) < 0)
			err_sys ("fork error");
		else if (pid > 0)
		{
			printf ("first son will exit pid = %d\n", getpid());
			exit (0);
		}

		sleep (2);
		printf ("second child, parent pid = %d\n", getppid());
		exit (0);
	}

	if (waitpid (pid, NULL, WNOHANG) != pid)
		err_sys ("waitpid error");

	//sleep (4);
	exit (0);
}


