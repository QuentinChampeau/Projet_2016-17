FLAGMATH=-lpthread -lm
CCFLAGS = -g

AVION	=avion
SGCA	=sgca
AVIONC	=$(AVION)/avion
SGCAC	=$(SGCA)/SGCA
SGCATCP	=$(SGCA)/lib/tcp/server
SGCAUDP	=$(SGCA)/lib/udp/client
AVIONTCP	=$(AVION)/lib/tcp/client
AVIONUDP	=$(AVION)/lib/udp/server




all: $(AVION).out $(SGCA).out

$(AVION).out: $(AVIONC).c $(AVIONTCP).o $(AVIONUDP).o
	gcc $(CCFLAGS) -o $(AVION).out $(AVIONC).c $(AVIONTCP).o $(AVIONUDP).o $(FLAGMATH)

$(SGCA).out: $(SGCAC).c $(SGCATCP).o $(SGCAUDP).o
	gcc $(CCFLAGS) -o $(SGCA).out $(SGCAC).c $(SGCATCP).o $(SGCAUDP).o $(FLAGMATH)

$(AVIONTCP).o: $(AVIONTCP).c $(AVIONTCP).h
	gcc $(CCFLAGS) -o $(AVIONTCP).o -c $(AVIONTCP).c
$(AVIONUDP).o: $(AVIONUDP).c $(AVIONUDP).h
	gcc $(CCFLAGS) -o $(AVIONUDP).o -c $(AVIONUDP).c

$(SGCATCP).o: $(SGCATCP).c $(SGCATCP).h
	gcc $(CCFLAGS) -o $(SGCATCP).o -c $(SGCATCP).c
$(SGCAUDP).o: $(SGCAUDP).c $(SGCAUDP).h
	gcc $(CCFLAGS) -o $(SGCAUDP).o -c $(SGCAUDP).c

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
	rm -f $(AVION).out $(SGCA).out $(AVIONTCP).o $(AVIONUDP).o $(SGCATCP).o $(SGCAUDP).o
