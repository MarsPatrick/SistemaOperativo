#include "unistd.h"
#include "stdio.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "errno.h"
#include "fcntl.h"
#include "pthread.h"

#define WRITE_INTERVAL 500*1000 // 500 milliseconds

void* reader(void* fd);

int main(){
  pthread_t readerThread;
  int readFd = open("myfifo", O_RDONLY|O_NONBLOCK);
  printf("hola");
  pthread_create( &readerThread, NULL, &reader, (void*) (&readFd));
}

void* reader(void* fd){
  // Form descriptor
  int readFd = (*(int*)fd);
  fd_set readset;
  int data = 0, err = 0, size = 0;
  // Initialize time out struct for select()
  struct timeval tv;
  tv.tv_sec = 0;
  tv.tv_usec = 10000;
  // Implement the receiver loop
  while(1) {
    // Initialize the set
    printf("hola");
    FD_ZERO(&readset);
    FD_SET(readFd, &readset);
    // Now, check for readability
    err = select(readFd+1, &readset, NULL, NULL, &tv);
    if (err > 0 && FD_ISSET(readFd, &readset)) {
      // Clear flags
      FD_CLR(readFd, &readset);
      // Do a simple read on data
      read(readFd, &data, sizeof(data));
      // Dump read data
      printf("\nReader: %d", data);
    }
  }
}