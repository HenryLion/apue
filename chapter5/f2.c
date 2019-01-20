#include "apue.h"

int main (void)
{
	FILE *fp, *fp2;
	fp = fopen ("f.c", "r");
	int chr = 0;
	chr = getc (fp);
	chr = getc (fp);
	
	//ungetc ('t', fp);
	//ungetc ('h', fp);
	putc ('$',fp);
	chr = getc (fp);

	printf ("%c\n", chr);
	fclose (fp);
	fp = fopen ("f.c", "r");
	fp2 = fopen ("f2.c", "r+");
	while (EOF != (chr = getc (fp)))
	{
		putc (chr, fp2);
	}
	fclose (fp);
	fclose (fp2);
	exit (0);
}
