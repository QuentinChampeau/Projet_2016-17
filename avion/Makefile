FLAGMATH=-lpthread -lm
CCFLAGS =

default: all

lib/udpserver.o: lib/udp/server.c lib/udp/server.h
	gcc $(CCFLAGS) -o lib/udpserver.o -c lib/udp/server.c;

lib/tcpclient.o: lib/tcp/client.c lib/tcp/client.h
	gcc $(CCFLAGS) -o lib/tcpclient.o -c lib/tcp/client.c;

all: lib/tcpclient.o lib/udpserver.o
	gcc $(CCFLAGS) -o avion.out lib/tcpclient.o lib/udpserver.o avion.c $(FLAGMATH)

clean:
	rm -f *.out *.o
