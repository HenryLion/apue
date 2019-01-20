#include "apue.h"
#include <unistd.h>

int main (void)
{
	if (link ("4_4.c", "link.c") < 0)
		err_sys ("link error!\n");
	
	// if (unlink ("link.c") < 0)
	//	err_sys ("unlink error!\n");

	exit (0);
}
