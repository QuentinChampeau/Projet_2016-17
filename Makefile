FLAGMATH=-lpthread -lm
CCFLAGS =
AVIONFD=avion
SGCAFD=sgca
AVION=		$(AVIONFD)/avion
SGCA=		$(SGCAFD)/SGCA
AVIONUDP=	$(AVIONFD)/lib/udp/server
AVIONTCP=	$(AVIONFD)/lib/tcp/client
SGCAUDP=	$(SGCAFD)/lib/udp/client
SGCATCP=	$(SGCAFD)/lib/tcp/server




all: avion.out SGCA.out

avion.out: avion/avion.c avion/lib/tcp/client.o avion/lib/udp/server.o
	gcc -g -o avion.out avion/avion.c avion/lib/tcp/client.o avion/lib/udp/server.o $(FLAGMATH)

SGCA.out: sgca/SGCA.c sgca/lib/tcp/server.o sgca/lib/udp/client.o
	gcc -g -o SGCA.out sgca/SGCA.c sgca/lib/tcp/server.o sgca/lib/udp/client.o $(FLAGMATH)

avion/lib/tcp/client.o: avion/lib/tcp/client.c avion/lib/tcp/client.h
	gcc -g -o avion/lib/tcp/client.o -c avion/lib/tcp/client.c
avion/lib/udp/server.o: avion/lib/udp/server.c avion/lib/udp/server.h
	gcc -g -o avion/lib/udp/server.o -c avion/lib/udp/server.c

sgca/lib/tcp/server.o: sgca/lib/tcp/server.c sgca/lib/tcp/server.h
	gcc -g -o sgca/lib/tcp/server.o -c sgca/lib/tcp/server.c
sgca/lib/udp/client.o: sgca/lib/udp/client.c sgca/lib/udp/client.h
	gcc -g -o sgca/lib/udp/client.o -c sgca/lib/udp/client.c

#
#lib/udpserver.o: lib/udp/server.c lib/udp/server.h
#	gcc $(CCFLAGS) -o lib/udpserver.o -c lib/udp/server.c;
#
#lib/tcpclient.o: lib/tcp/client.c lib/tcp/client.h
#	gcc $(CCFLAGS) -o lib/tcpclient.o -c lib/tcp/client.c;
#
#all: lib/tcpclient.o lib/udpserver.o
#	gcc $(CCFLAGS) -o avion.out lib/tcpclient.o lib/udpserver.o avion.c $(FLAGMATH)
#
clean:
	rm -f avion.out SGCA.out avion/lib/tcp/client.o avion/lib/udp/server.o sgca/lib/tcp/server.o sgca/lib/udp/client.o
