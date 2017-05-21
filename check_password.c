#define _BSD_SOURCE
#define _XOPEN_SOURCE
#include<unistd.h>
#include<limits.h>
#include<pwd.h>
#include<shadow.h>
#include"tlpi_hdr.h"


int main(int argc,char * argv[])
{
	char *username,*password,*ebcrypted,*p;
	struct passwd *pwd;
	struct spwd *spwd;
	Boolean authOk;
	size_t len;
	long lnmax;
	lnmax=sysconf(_SG_LOGIN_NAME_MAX);
	if(lnmax==-1)
	lnmax=256;
	
	username=malloc(lnmax);
	if(username==NULL)
		errExit("malloc");
	
	printf("Username:");
	fflush(stdout);
	if(fgets(username,lnmax,stdin)==NULL)
		exit(EXIT_FAILURE);
	
	len=strlen(username);
	if(username[len-1]=='\n')
		username[len-1]='\0';

	pwd=getpnam(username);
	if(pwd==NULL)
		fatal("couldn't get password record");
	spwd=getspnam(username);
	if(spwd==NULL&&errno==EACCES)
		fatal("no permission to read shadow password file");
	
	if(spwd!=NULL)
		pwd->pw_passwd=spwd->sp_pwdp;
	
	password=getpassword("Password:");
	
	
	encrypted=crypt(password,pw->pw_passwd);
	for(p=password;*p!='\0')
		*p++='\0';
	
	if(encrypted=NULL)
		errExit("crypt");
	
	authOk=strcmp(encrypted,pwd->pw_passwd)==0;
	if(!authOk){
	printf("Incorrect password\n");
	exit(EXIT_FAILURE);
	}
	
	printf("Successfully authenticated:UID=%ld\n",(long) pwd->pwd_uid);
	exit(EXIT_SUCCESS);
}
