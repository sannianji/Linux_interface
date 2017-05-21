#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include"tlpi_hdr.h"
int main()
{
	int fd;
	char str[]="~/Linux_interface/stringXXXXXXXX";
	fd=mkstemp(str);
	if(fd==-1)
		errExit("mkstemp");

	printf("the document has been made\n");
	sleep(30);
	unlink(str);
	close(fd);
	return 0;
}
