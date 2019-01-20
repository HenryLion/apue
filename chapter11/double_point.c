#include <stdio.h>
#include <stdlib.h>

void my_malloc (void **p, size_t size)
{
	printf ("0x%x\n", (unsigned int)*p);
	*p = malloc (size);
	printf ("0x%x\n", (unsigned int)*p);
	
}

int main (void)
{
	int *p ;
	printf ("0x%x\n", (unsigned int)p);

	my_malloc ((void**)&p, 4);
	printf ("0x%x\n", (unsigned int)p);
	if (NULL == p)
		printf ("NULL\n");
	return 0;
}

