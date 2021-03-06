#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define FIFONAME "myfifo"

int main (void){
	int n,fd,pid;
	char buf[1024];
	char * mypid = malloc(6);
	pid = getpid();
	sprintf(mypid,"%d",pid);
	if((fd=open(FIFONAME,O_RDWR))<0){
		perror("open");
		exit(1);
	}
	write(fd," ",sizeof(" "));
	while((n=read(0,buf,sizeof(buf)))>0){
		write(fd,buf,n);
	}
	close(fd);
	exit(0);
}