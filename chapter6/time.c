#include <time.h>
#include "apue.h"

int main (void)
{
	time_t time_now;
	time (&time_now);

	struct tm *lt = localtime (&time_now);

	char buf[1024] = {0};

	strftime (buf, 1024, "%F", lt);
	printf ("%s\n", buf);
	return 0;
}
