#define _GNU_SOURCE
#include<unistd.h>
#include<sys/fsuid.h>
#include<limits.h>
#include"ugid_functions.h"
#include"tlpi_hdr.h"

#define SG_SIZE (NGROUPS_MAX + 1)

int main(int argc,char *argv)
{
	uid_t ruid,euid,suid,fsuid;
	gid_t rgid,egid,sgid,fsgid;
	gid_t suppGroups[SG_SIZE];
	int numGroups,j;
	char *p;
	
	if(getresuid(&ruid,&euid,&suid)==-1)
		errExit("getresuid");
	if(getresgid(&rgid,&egid,&sgid)==-1)
		errExit("getresgid");
	
	fsuid = setfsuid(0);
	fsgid = setfsgid(0);

	printf("UID: ");
	p=userNameFromId(ruid);
	printf("real=%s (%ld);",(p==NULL)?"???":p,(long) ruid);
	p=userNameFromId(euid);
	printf("real=%s (%ld);",(p==NULL)?"???":p,(long) euid);
	p=userNameFromId(suid);
	printf("real=%s (%ld);",(p==NULL)?"???":p,(long) suid);
	p=userNameFromId(fsuid);
	printf("real=%s (%ld);",(p==NULL)?"???":p,(long) fsuid);
	printf("\n");

	printf("GID: ");
	p=groupNameFromId(rgid);
	printf("real=%s (%ld);",(p==NULL)?"???":p,(long) rgid);
	p=groupNameFromId(egid);
	printf("real=%s (%ld);",(p==NULL)?"???":p,(long) egid);
	p=groupNameFromId(sgid);
	printf("real=%s (%ld);",(p==NULL)?"???":p,(long) sgid);
	p=groupNameFromId(fsgid);
	printf("real=%s (%ld);",(p==NULL)?"???":p,(long) fsgid);
	printf("\n");
	
	numGroups=getgroups(SG_SIZE,suppGroups);
	if(numGroups==-1)
		errExit("getgroups");
	printf("Supplementary groups (%d):",numGroups);
	for(j=0;j<numGroups;j++)
	{
		p=groupNameFromId(suppGroups[j]);
		printf("%s (%ld)",(p==NULL)?"???":p,(long) suppGroups[j]);
	}

	printf("\n");
	
	exit(EXIT_SUCCESS);
}
