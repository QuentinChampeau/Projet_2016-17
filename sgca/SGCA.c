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
#define PORTMULTIJAVA 2345
/* 224.0.0.0 à 239.255.255.255 */
#define MULTICASTGROUP  "224.0.0.1" // 0x010000e0 224.0.0.1

/* connexion TCP */
#define PORTTCP 1234

#define MAX_BUF_LEN 256

struct avionS AVIONS;

void *ecouteAvion(void *socket) {
    int sock = *((int*)socket);
    int compteur = 0;
    struct avion av;
    int numAvion = AVIONS.n;
    while (read(sock, &av, sizeof(struct avion)) != 0) {
        if (compteur == 0) {
            AVIONS.n = AVIONS.n + 1;
            AVIONS.data[AVIONS.n-1] = av;
            printf("Nouvel avion \"%s\"\n", av.num_vol);
            compteur++;
        }
        printf("Avion %s -> localisation : (%d,%d), altitude : %d, vitesse : %d, cap : %d\n",
   av.num_vol, av.x, av.y, av.altitude, av.vitesse, av.cap);
        AVIONS.data[numAvion] = av;
        sleep(2);
    }
    printf("Avion \"%s\" quitté.\n", av.num_vol);
    AVIONS.n = AVIONS.n-1;
    //free(AVIONS.data[numAvion]);
    //AVIONS.data[numAvion] = NULL;
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


char *RemplirInfosTousAvions() {
    char *s = malloc(AVIONS.n * sizeof(struct avion));
    char *s2 = malloc(sizeof(struct avion));
    sprintf(s, "%d\n", AVIONS.n);
    int i;
    for (i=0; i<AVIONS.n; i++) {
        sprintf(s2, "%s%d%d%d%d%d\n", 
            AVIONS.data[i].num_vol, AVIONS.data[i].x, AVIONS.data[i].y, AVIONS.data[i].altitude, AVIONS.data[i].cap, AVIONS.data[i].vitesse);

        strcat(s, s2);
        /*strcat(s, AVIONS.data[i].num_vol);
        strcat(s, AVIONS.data[i].x);
        strcat(s, AVIONS.data[i].y);
        strcat(s, AVIONS.data[i].altitude);
        strcat(s, AVIONS.data[i].cap);
        strcat(s, AVIONS.data[i].vitesse);
        */
    }
    //printf("%s\n", *s);
    free(s2);
    printf("%s\n", s);
    return s;
}

int main(int argc, char *argv[])
{
    pthread_t threadtcp;
    int portTCP, portUDPAvion, portUDPJava = PORTMULTIJAVA;
    char *IPudp = MULTICASTGROUP;
    portUDPAvion = PORTMULTI;
    portTCP = PORTTCP;
    int  UDPMcastClient, UDPServerView, UDPServerCtrl;
    /**
     * Multicast
     * UDP client
     */
    struct sockaddr_in tmpInfo; // avion
    struct sockaddr_in javaInfo; // java
    AVIONS.n = 0;
    // 50 avions max
    AVIONS.data = malloc(sizeof(struct avion) * 50);
    

    /**
     * UDP multicast pour avions
     */
    if (UDPMulticast(&UDPMcastClient, IPudp, portUDPAvion, &tmpInfo) < 0) {
        perror("UDPMulticast SGCA multicast");
        exit(EXIT_FAILURE);
    }

    /**
     * UDP multicast pour java
     */
    if (UDPMulticast(&UDPServerView, IPudp, portUDPJava, &javaInfo) < 0) {
        perror("UDPMulticast SGCA multicast");
        exit(EXIT_FAILURE);
    }
    char *tousAvions;
    /* Création struct de connexion à envoyer au client */
    printf("envoie de %d vers %s:%d \n", portTCP, IPudp, portUDPAvion);

    if (pthread_create(&threadtcp, NULL, tcpConnexion, &portTCP) < 0) {
        perror("thread tcp error");
        return -1;
    }


    while (1) {

        sendto(UDPMcastClient, &portTCP, sizeof(int), 0, (struct sockaddr *) &tmpInfo, sizeof(tmpInfo));

        // envoie données aux consoles java
        tousAvions = malloc(AVIONS.n * sizeof(struct avion) + sizeof(int));
        tousAvions = RemplirInfosTousAvions();

        sendto(UDPServerView, &tousAvions, sizeof(tousAvions), 0, (struct sockaddr *) &javaInfo, sizeof(javaInfo));

        free(tousAvions);

        sleep(2);

    }


    return 0;

}
