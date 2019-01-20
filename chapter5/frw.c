#include "apue.h"

int main (void)
{
	float data[5] = { 2.2323, 3.53543, 5.2222, 1.3325, 9.3020};
	FILE *fp;
	fp = fopen ("rw.c", "r+");
	fwrite (&data[0], sizeof (float), 3, fp);
	fclose (fp);
	exit (0);
}


