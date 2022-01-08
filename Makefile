CC=gcc
CFLAGS= 
NS=sv
NC=cl
all: server cliente tuberia

server: $(NS).c
	$(CC) $(NS).c -o $(NS) $(CFLAGS)
cliente: $(NC).c
	$(CC) $(NC).c -o $(NC) $(CFLAGS)
tuberia:
	mkfifo myfifo -m 666
