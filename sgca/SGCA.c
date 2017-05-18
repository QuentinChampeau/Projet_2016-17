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
 #include <pthread.h>

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

void* tcpConnexion(int TCPServer) {
    char *buffer = malloc(MAX_BUF_LEN);
    
    printf("coucou\n");

    while (1) {
        printf("on lit\n");
        if (recv(TCPServer, &buffer, sizeof(buffer), 0) < 0) {
            perror("recv");
        }
    }
    //send(comm_sock, buffer, strlen(buffer), 0);
    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    pthread_t threadtcp;
    int TCPServer, UDPMcastClient, UDPServerView, UDPServerCtrl;
    char* buffer       = malloc( MAX_BUF_LEN );
    /**
     * Multicast
     * UDP client
     */
    struct sockaddr_in tmpInfo;

    //char* buffer       = malloc( MAX_BUF_LEN );
    uint32_t tcpaddr;
    uint16_t tcpport;

    //tcpaddr = htonl(MULTICASTGROUP);
    //tcpport = ntohs(PORTMULTI);


    if (UDPMulticast(&UDPMcastClient, MULTICASTGROUP, PORTMULTI, &tmpInfo) < 0) {
        perror("UDPMulticast SGCA multicast");
        exit(EXIT_FAILURE);
    }


    /* Création struct de connexion à envoyer au client */
    tcpport = 1234;
    int socklen = sizeof(struct sockaddr_in);
    printf("envoie de %d vers %s:%d \n", tcpport, MULTICASTGROUP, PORTMULTI);
    memcpy(buffer, &tcpport, sizeof(uint16_t));
    if (connectTCP(&TCPServer, "coucou", PORTTCP) < 0) {
        perror("connectTCP SCA failed");
        exit(EXIT_FAILURE);
    }
    while (1) {

        sendto(UDPMcastClient, buffer, MAX_BUF_LEN, 0, (struct sockaddr *) &tmpInfo, sizeof(tmpInfo));
        if (pthread_create(&threadtcp, NULL, tcpConnexion, tcpport) < 0) {
            perror("thread tcp error");
            return -1;
        }
    }
    return 0;

}
