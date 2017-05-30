#define _BSD_SOURCE
#define _XOPEN_SOURCE
#include<unistd.h>
#include<limits.h>
#include<pwd.h>
#include<shadow.h>
#include"tlpi_hdr.h"

int main(int argc,char *argv[])
{
	char *username,*password,*encrypted,*p;
	struct passwd *pwd;
	struct spwd *spwd;
	Boolean authOk;
	size_t len;
	long lnmax;
		
	lnmax=sysconf(_SC_LOGIN_NAME_MAX);
	if(lnmax==-1)	
		lnmax=256;
	
	username=malloc(lnmax);
	if(username==NULL)
		errExit("malloc");
	
	printf("Username: ");
	fflush(stdout);
	if(fgets(username,lnmax,stdin)==NULL)
		exit(EXIT_FAILURE);
	spwd=getspnam(username);
	if(spwd==NULL && errno==EACCES)
		fatal("no permissed to read shadow password file");
	
	if(spwd!=NULL)
		pwd->pw_passwd=spwd->sp_pwdp;
	
	password=getpass("Password: ");
	encrypted=crypt(password,pwd->pw_passwd);
	
	for(p=password;*p!='\0';)
		*p++ = '\0';
	
	if(encrypted==NULL)
		errExit("crypt");
	
	authOk=strcmp(encrypted,pwd->pw_passwd)==0;
	if(!authOk)
	{
		printf("Inconrrect password\n");
		exit(EXIT_FAILURE);
	}

	printf("Successfully authenticatedL UID=%ld\n",(long) pwd->pw_uid);
	
	exit(EXIT_SUCCESS);
}
