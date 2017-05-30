#include "tlpi_hdr.h"

extern char **environ;


int main(int argc,char *argv[])
{
	char **p=environ;
	for(;p!=NULL;p++)
		puts(*p);
	exit(EXIT_SUCCESS);
}
