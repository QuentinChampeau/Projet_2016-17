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

int port = 1027;
int nouveau_port() {
    /* compris entre 1024-65535 */
    return port++;
}

//the thread function
void *connection_handler(void *);

int connexionTCP () {
    int socket_desc , client_sock , c , read_size;
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
    server.sin_port = htons( port );

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
    pthread_t thread_id;

    /*********************************************************/
    /*************** Multicast *******************************/
    /*********************************************************/

    int sock;
    struct sockaddr_in groupSock;
    struct in_addr localInterface;
    unsigned char mc_ttl=1;     /* time to live (hop count) */

    /* create a socket for sending to the multicast address */
    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP /* ou 0 */)) < 0) {
        perror("socket");
        exit(1);
    }

    /* set the TTL (time to live/hop count) for the send */
    if(setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, (char *) &mc_ttl, sizeof(mc_ttl)) < 0)
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

    /* envoie d'un port à un avion pour la socket TCP */
    char message[100];
    sprintf(message, "%d", port);

    while (1) {
        int send_len = sizeof(message);
        if (sendto(sock, &message, send_len, 0, (struct sockaddr *) &groupSock, sizeof(groupSock)) != send_len) {
           perror("sendto");
           exit(1);
        }
        sleep(1);
        //pthread_create  (&thread_id,  NULL, &connexionTCP, NULL);
    }

    /*connexionTCP
    multicast();
    */
    return 0;

}
