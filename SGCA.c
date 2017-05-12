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
#include "avion.h"


#define MSGBUFSIZE 256

/* multicast */
/*  1024 à 65535 */
#define PORTMULTI 12345
/* 224.0.0.0 à 239.255.255.255 */
#define MULTICASTGROUP "225.0.0.37"

/* connexion TCP */
#define PORTTCP 1234
#define HOST "localhost" /* 127.0.0.1 */

#define MAXPENDING 1


struct sockaddr_in creationConnexionTCP () {
    struct sockaddr_in server;


    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;                /* Internet address family */
    server.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    server.sin_port = htons(PORTTCP);      /* Local port */


    return(server);
}

int connexionTCP () {
    int socket_desc, client_sock, c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        perror("Could not create socket");
        exit(EXIT_FAILURE);
    }
    puts("Socket created");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; /* nous sommes un serveur, nous acceptons n'importe quelle adresse */
    server.sin_port = htons( PORTTCP );

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        exit(EXIT_FAILURE);
    }
    puts("bind done");

    //Listen
    if (listen(socket_desc , 5) < 0) {
    	perror("listen");
    	exit(EXIT_FAILURE);
    }

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    puts("Connection accepted");

    //Receive a message from client
    while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
    {
        //Send the message back to client
        write(client_sock , client_message , strlen(client_message));
    }

    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
     return 0;
}

int main(int argc, char *argv[])
{

    /*********************************************************/
    /*************** Multicast *******************************/
    /*********************************************************/

    int sockMulticast, socketTCP, socketClient, socketServer;
    struct sockaddr_in groupSock;
    struct in_addr localInterface;
    unsigned char mc_ttl=1;     /* time to live (hop count) */
    struct coordonnees coord;

    /* create a socket for sending to the multicast address */
    if ((sockMulticast = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP /* ou 0 */)) < 0) {
        perror("socket");
        exit(1);
    }

    /* set the TTL (time to live/hop count) for the send */
    if(setsockopt(sockMulticast, IPPROTO_IP, IP_MULTICAST_TTL, (char *) &mc_ttl, sizeof(mc_ttl)) < 0)
    {
      perror("Setting local interface error");
      exit(1);
    }

    /* construct a multicast address structure */
    memset(&groupSock, 0, sizeof(groupSock));
    /*struct sockaddr_in {
        // __uint8_t       sin_len;
        sa_family_t     sin_family;
        in_port_t       sin_port;
        struct  in_addr sin_addr;
        char            sin_zero[8];
    };*/
    groupSock.sin_family = AF_INET;
    groupSock.sin_port = htons(PORTMULTI);
    groupSock.sin_addr.s_addr = inet_addr(MULTICASTGROUP);

    /***********************************/
    /****** socket multicast crée ******/
    /***********************************/

    int pid = fork();

    struct sockaddr_in nouveauServer = creationConnexionTCP();

    if (pid == 0) {
        /**
         * On envoie via le multicastla structure de la socket TCP
         */
        int send_len = sizeof(nouveauServer);
        if (sendto(sockMulticast, &nouveauServer, send_len, 0, (struct sockaddr *) &groupSock, sizeof(groupSock)) != send_len) {
           perror("sendto");
           exit(1);
        }
        sleep(1);
    } else {
        /**
         * On lit les données de l'avion via TCP
         */
        /* Create socket for incoming connections */
        if ((socketTCP = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
            perror("socket() failed");

        /* Bind to the local address */
        if (bind(socketTCP, (struct sockaddr *) &nouveauServer, sizeof(nouveauServer)) < 0)
            perror("bind() failed");

        /* Mark the socket so it will listen for incoming connections */
        if (listen(socketTCP, MAXPENDING) < 0)
            perror("listen() failed");

        socklen_t tailleCoord;
        socklen_t taillesocketServer;
        while(1) {
            tailleCoord = sizeof(struct coordonnees);
            taillesocketServer = sizeof(socketServer);
            if ((socketClient = accept(socketTCP, (struct sockaddr *) &coord, &tailleCoord)) < 0) {
                perror("accept failed");
            }
            if(recvfrom(socketTCP, &coord, tailleCoord, 0, (struct sockaddr *) &socketServer, &taillesocketServer) < 0) {
                perror("recvfrom");
            }
            printf("avion y %d\n", coord.y);

        }
    }


    /*connexionTCP
    multicast();
    */
    return 0;

}
