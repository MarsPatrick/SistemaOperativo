#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define FIFONAME "myfifo"

int main (void){
	int n,fd,pid,primer;
	char buf[1024];
	char * mypid = malloc(6);
	pid = getpid();
	sprintf(mypid,"%d",pid);
	if((fd=open(FIFONAME,O_RDWR))<0){
		perror("open");
		exit(1);
	}
	primer=0;
	while((n=read(0,buf,sizeof(buf)))>0){
		if(primer==0){
			write(fd,mypid,sizeof(mypid));
			primer++;
		}
		write(fd,buf,n);
	}
	close(fd);
	exit(0);
}
