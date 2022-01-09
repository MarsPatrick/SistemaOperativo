#include "unistd.h"
#include "stdio.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "errno.h"
#include "fcntl.h"
#include "pthread.h"

#define WRITE_INTERVAL 500*1000 // 500 milliseconds

void writer(void* fd);

int main(){
  int writeFd = open("myfifo", O_WRONLY|O_NONBLOCK);
  writer((void*) (&writeFd));
}

void writer(void* fd){
  // Form descriptor
  int writeFd = (*(int*)fd);
  static int var = 0;
  while(1) {
    // Form data to be written on pipe
    printf("\nWriter: %d", var);
    // Do a simple write
    write(writeFd, (int*)(&var), sizeof(var));
    // Increment the variable, so that we can see the incremental communication
    var++;
    // Give interval between next write
    usleep(WRITE_INTERVAL);
  }
}