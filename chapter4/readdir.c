#include "apue.h"
#include <dirent.h>

const char *p = "/home/hanb/workspace/apue/chapter4/testdir/";

int main (void)
{
	DIR *dp;
	if ((dp = opendir (p)) == NULL)
		printf ("can't open dir\n");
	else
		printf ("open dir success\n");
	closedir (dp);
	return 0;
}
