CC=gcc
CSFLAGS= -pthread
CCFLAGS=
NS=sv
NC=cl
all: server cliente tuberia

server: $(NS).c
	$(CC) $(NS).c -o $(NS) $(CSFLAGS)
cliente: $(NC).c
	$(CC) $(NC).c -o $(NC) $(CCFLAGS)
tuberia:
	mkfifo myfifo -m 666
