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
#include "../avion/stub.h"
 #include <pthread.h>


/* multicast */
/*  1024 à 65535 */
#define PORTMULTI   8888
/* 224.0.0.0 à 239.255.255.255 */
#define MULTICASTGROUP  "224.0.0.1" // 0x010000e0 224.0.0.1

/* connexion TCP */
#define PORTTCP 1234

#define MAX_BUF_LEN 256


void *ecouteAvion(void *socket) {
    int sock = *((int*)socket);
    int compteur = 0;
    struct avion av;
    while (read(sock, &av, sizeof(struct avion)) != 0) {
        if (compteur == 0) {
            printf("Nouvel avion \"%s\"\n", av.num_vol);
            compteur++;
        }
        printf("Avion %s -> localisation : (%d,%d), altitude : %d, vitesse : %d, cap : %d\n",
   av.num_vol, av.x, av.y, av.altitude, av.vitesse, av.cap);
        sleep(2);
    }
    printf("Avion \"%s\" quitté.\n", av.num_vol);

    return 0;
}

void* tcpConnexion(void *portTCP) {
    struct sockaddr_in target;
    int port = *((int*)portTCP);
    pthread_t nouveauThread;
    int TCPServer;
    int nvelleSock = 0;


    if (connectTCP(&TCPServer, port) < 0) {
        perror("connectTCP SCA failed");
        exit(EXIT_FAILURE);
    }
        socklen_t addrlen = sizeof(struct sockaddr_in);

    while (1) {
        nvelleSock = accept(TCPServer, (struct sockaddr*) &target, &addrlen);
        if (nvelleSock < 0) {
            perror("accept serveur");
            exit(EXIT_FAILURE);
        }

        pthread_create(&nouveauThread, NULL, ecouteAvion, &nvelleSock);
    }

}


int main(int argc, char *argv[])
{
    pthread_t threadtcp;
    int portTCP, portUDP;
    char *IPudp = MULTICASTGROUP;
    portUDP = PORTMULTI;
    portTCP = PORTTCP;
    int  UDPMcastClient, UDPServerView, UDPServerCtrl;
    /**
     * Multicast
     * UDP client
     */
    struct sockaddr_in tmpInfo;


    if (UDPMulticast(&UDPMcastClient, IPudp, portUDP, &tmpInfo) < 0) {
        perror("UDPMulticast SGCA multicast");
        exit(EXIT_FAILURE);
    }


    /* Création struct de connexion à envoyer au client */
    printf("envoie de %d vers %s:%d \n", portTCP, IPudp, portUDP);

    if (pthread_create(&threadtcp, NULL, tcpConnexion, &portTCP) < 0) {
        perror("thread tcp error");
        return -1;
    }

    while (1) {

        sendto(UDPMcastClient, &portTCP, sizeof(int), 0, (struct sockaddr *) &tmpInfo, sizeof(tmpInfo));
        sleep(2);

    }


    return 0;

}
