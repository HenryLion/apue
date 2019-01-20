#include "apue.h"
#include <sys/wait.h>

char *env_init[] = { "USER=unknown", "PATH=/tmp", NULL};

int main (void)
{
	pid_t pid;
	if ((pid = fork () ) < 0)
		err_sys ("fork error");
	else if (pid == 0)
	{
		if (execle ("dl /* /home/hanb/workspace/apue/chapter8/8_6 */ ", "echoall", "myarg1",
			"MY ARG2", (char*) 0, env_init) < 0)
			printf ("pid = %d, ppid = %d\n", getpid(), getppid());
			err_sys ("execle error");
	}

	printf ("1: pid = %d\n", getpid());
	if (waitpid (pid, NULL, 0) < 0)
		err_sys ("wait error");

	if (( pid = fork ()) < 0)
		err_sys ("fork error");
	else if (pid == 0)
	{
		if (execlp ("8_6", "echoall", "only 1 arg", (char*) 0) < 0)
			err_sys ("execlp error");
		printf ("hello, world\n");
	}
	printf ("2: pid = %d\n", getpid());
	exit (0);
}


