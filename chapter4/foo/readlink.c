#include "apue.h"
#include <unistd.h>

int main (void)
{
	ssize_t read_size;
	char buf[20] = {0};
	if (read_size = readlink ("link_4_4.c", buf, 20) < 0)
		err_sys ("readlink error");

	printf ("%s\n", buf);
	exit (0);
}
