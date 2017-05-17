FLAGMATH=-lpthread -lm
CCFLAGS =

default: all

lib/udpclient.o: lib/udp/client.c lib/udp/client.h
	gcc $(CCFLAGS) -o lib/udpclient.o -c lib/udp/client.c;

lib/tcpclient.o: lib/tcp/client.c lib/tcp/client.h
	gcc $(CCFLAGS) -o lib/tcpclient.o -c lib/tcp/client.c;

all: lib/tcpclient.o lib/udpclient.o
	gcc $(CCFLAGS) -o avion.out lib/tcpclient.o lib/udpclient.o avion.c $(FLAGMATH)

clean:
	rm -f *.out *.o
