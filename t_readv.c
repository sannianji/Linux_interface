#include<sys/stat.h>
#include<sys/uio.h>
#include<fcntl.h>
#include"tlpi_hdr.h"

int main(int argc,char *argv[])
{
	int fd;
	struct iovec iov[3];
	struct stat myStruct;
	int x;
#define STR_SIZE 100
	char str[STR_SIZE];
	ssize_t numRead,totRequired;
	
	if(argc!=3||strcmp(argv[1],"--help")==0)
		usageErr("%s fileread filewrite\n",argv[0]);
	
	fd=open(argv[1],O_RDONLY);
	if(fd==-1)
		errExit("read open");
	
	totRequired=0;
	
	iov[0].iov_base=&myStruct;
	iov[0].iov_len=sizeof(struct stat);
	totRequired+=iov[0].iov_len;
	
	iov[1].iov_base=&x;
	iov[1].iov_len=sizeof(x);
	totRequired+=iov[1].iov_len;

	iov[2].iov_base=str;
	iov[2].iov_len=STR_SIZE;
	totRequired+=iov[2].iov_len;
	
	numRead=readv(fd,iov,3);
	if(numRead==-1)
		errExit("readv");
	
	if(numRead<totRequired)
		printf("Read fewer bytes than required\n");
	
	printf("total required :%ld; bytes read:%ld\n",(long) totRequired,(long) numRead);

	int fd2=open(argv[2],O_WRONLY|O_CREAT);
	if(fd2==-1)
		errExit("write open");

	int numWrite=writev(fd2,iov,3);
	if(numWrite==-1)
		errExit("writev");
	if(numWrite<totRequired)	
		printf("Write fewer byts than required\n");
	
	printf("total required:%ld; bytes write:%ld\n",(long) totRequired,(long) numWrite);
	exit(EXIT_SUCCESS);
}
