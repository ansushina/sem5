#include <stdio.h>
#include <unistd.h>

int main()

{
	int childpid, pearentpid;
	if ((childpid = fork())== -1)
	{
		perror("Cant fork.\n");
		return 1;
	}
	else if (childpid == 0)
	{
		while (1) printf("%d ", getpid());
		return 0;
	}
	else
	{
		while(1) printf("%d ",getpid());
		return 0;

	}
}
