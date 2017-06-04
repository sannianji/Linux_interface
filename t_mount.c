#include<sys/mount.h>
#include"tlpi_hdr.h"

static voud usageError(const char *progName,const char *msg)
{
	if(msg!=NULL)
		fprintf(stderr,"%s",msg);
	
	fprintf(stderr,"Usage:%s {options} source target\n\n",progName);
	fprintf(stderr,"Available options:\n");
#define fpe(str) fprintf(stderr,"   " str)
	fpe(-t)
}
