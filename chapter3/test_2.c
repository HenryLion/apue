#include "apue.h"
#include <errno.h>
#include <limits.h>


/* write your own dup2 function */

#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else
static long openmax = 0;
#endif

#define OPEN_MAX_GUESS 256

long open_max (void)
{
	if (openmax == 0)
	{
		errno = 0;
		if ((openmax = sysconf (_SC_OPEN_MAX)) < 0)
		{
			if (errno == 0)
				openmax = OPEN_MAX_GUESS;
			else
				err_sys ("sysconf error for _SC_OPEN_MAX");
		}
	}
	return openmax;
}

int my_dup2 (int fd, int fd_des)
{
	long arr_len = open_max ();
	int *pfd = (int *)malloc (sizeof (int) * arr_len);
	int index = 0;
	int close_index = 0;
	int temp_fd = 0;
	for (index = 0; index < arr_len; ++index)
	{
		temp_fd = dup (0);
		if (temp_fd == fd_des)
			break;
		else
		{
			pfd[index] = temp_fd;
		}
	}

	for (close_index = 0; close_index <= index; ++close_index)
	{
		close (pfd[close_index]);
	}

	free (pfd);
	return temp_fd;
}

int main (void)
{
	int newfd = 1001;
	char buf[20] = "hello, world!\n";
	long fdmax = open_max();
	printf ("%ld\n", fdmax);
	int dup_fd = my_dup2 (STDOUT_FILENO, newfd);
	printf ("%d\n", dup_fd);
	write (newfd, buf, 20);

	exit (0);
}
