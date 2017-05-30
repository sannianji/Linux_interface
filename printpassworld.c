#include<stdio.h>
#include<pwd.h>
int main()
{
	struct passwd *pwd;
	while((pwd=getpwent())!=NULL)
		printf("%-8s\t %5ld\n",pwd->pw_name,(long) pwd->pw_uid);
	endpwent();
}
