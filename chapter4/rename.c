#include "apue.h"
#include <stdio.h>

int main (int argc, char *argv[])
{
	if (3 != argc)
		err_sys ("usage: a.out [oldname] [newname]");
	
	if (rename (argv[1], argv[2]) < 0)
		err_sys ("rename error");

	exit (0);
}
