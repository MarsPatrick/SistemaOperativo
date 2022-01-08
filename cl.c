#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#define FIFONAME "myfifo"

int main (void){
	int n,fd;
	char buf[1024];
	if((fd=open(FIFONAME,O_RDWR))<0){
		perror("open");
		exit(1);
	}
	write(1,buf,n);
	while((n=read(0,buf,sizeof(buf)))>0){
		write(fd,buf,n);
		write(1,buf,n);
	}
	close(fd);
	exit(0);
}
