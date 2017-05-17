#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <sys/errno.h>  /* errno */
#include <stdlib.h>     /* exit */
#include <getopt.h>     /* getopt_long */
#include <limits.h>     /* LONG_MAX, LONG_MIN */
#include "lib/avion.h"
#include "lib/udp/client.h"
#include "lib/tcp/server.h"

#define MSGBUFSIZE 256

/* multicast */
/*  1024 à 65535 */
#define PORTMULTI   8888
/* 224.0.0.0 à 239.255.255.255 */
#define MULTICASTGROUP  "224.0.0.1" // 0x010000e0 224.0.0.1

/* connexion TCP */
#define PORTTCP 1234
#define HOST "localhost" /* 127.0.0.1 */

#define MAXPENDING 1
#define MAX_BUF_LEN 256




int main(int argc, char *argv[])
{
    int TCPServer, UDPMcastClient, UDPServerView, UDPServerCtrl;
    char* buffer       = malloc( MAX_BUF_LEN );
    strcpy(buffer, "hey\n");
    /**
     * Multicast
     * UDP client
     */
    struct sockaddr_in tmpInfo;
    
    
    //char* buffer       = malloc( MAX_BUF_LEN );
    uint32_t tcpaddr;
    uint16_t tcpport;

    if (UDPMulticast(&UDPMcastClient, MULTICASTGROUP, PORTMULTI, &tmpInfo) < 0) {
        perror("connectTCP SGCA multicast");
        exit(EXIT_FAILURE);
    }

    int socklen = sizeof(struct sockaddr_in);
    while (1) {
        printf("envoie  from %s:%d \n", MULTICASTGROUP, PORTMULTI);

        sendto(UDPMcastClient, buffer, MAX_BUF_LEN, 0, (struct sockaddr *) &tmpInfo, sizeof(tmpInfo));
    }
    return 0;

}
