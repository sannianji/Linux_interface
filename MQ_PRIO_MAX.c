#include<stdio.h>
#include<limits.h>
#include<unistd.h>
int main()
{
printf("%ld",sysconf(MQ_PRIO_MAX));
}
