#include "apue.h"

int main (void)
{
	int ter;
	ter = fileno (stdin);
	printf ("%d\n", ter);
	ter = fileno (stdout);
	printf ("%d\n", ter);
	ter = fileno (stderr);
	printf ("%d\n", ter);

	exit (0);
}
