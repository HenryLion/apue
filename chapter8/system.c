#include "apue.h"

int main (void)
{
	FILE *fp;
	int count = 0;
	while (1)
	{
		count++;
		fp = fopen ("result", "w");
		system ("./8_6 > result");
		fflush (fp);
		fclose (fp);
		fp = fopen ("result", "r");
		int c = getc (fp);
		if (c == 'd')
		{
			printf ("\n%c\n", c);
			break;
		}
		fclose (fp);
		printf ("%d\r", count);
	}
	// printf ("%d\n", count);
	return 0;
}
