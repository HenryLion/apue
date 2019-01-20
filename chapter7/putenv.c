#include "apue.h"

int main (void)
{
	if (NULL == getenv ("HAHAHOU"))
		printf ("no environ name is HAHAHOU\n");

	putenv ("HAHAHOU=tianshangrenjian");

	if (NULL == getenv ("HAHAHOU"))
		printf ("no environ name is HAHAHOU\n");
	else
		printf ("%s\n", getenv ("HAHAHOU"));

	return 0;
}
	
