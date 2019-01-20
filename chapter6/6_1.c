#include <pwd.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

/*
struct passwd * my_getpwnam (const char *name)
{
	struct passwd *ptr;
	setpwent ();
	while ((ptr = getpwent ()) != NULL)
		if (strcmp (name, ptr->pw_name) == 0)
			break;
	endpwent ();
	return (ptr);
}
*/
int main (void)
{
	struct passwd *ptr = getpwnam ("root");
	printf ("%d-%d\n",ptr->pw_uid, ptr->pw_gid);
	return 0;
}

