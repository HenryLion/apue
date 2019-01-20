#include "apue.h"
int main (void)
{
	FILE *fp;
	fp = fopen ("f.c", "r");
	char buf[10];
	while (fgets (buf, 10, fp) != NULL)
	{
		if (fputs (buf, stdout) == EOF)
			err_sys ("output error");
	}
	if (ferror (stdin))
		err_sys ("input error");
	fclose (fp);
	exit (0);
}
