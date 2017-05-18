#include "client.h"




int connectTCP(int* pSocket, const char *pAddr, const int pPort){

	/* [0] initialize variables
	=========================================================*/
	struct sockaddr_in target;


	/**
	 * Création socket
	 */
	*pSocket = socket(AF_INET, SOCK_STREAM, 0);

	if( *pSocket < 0 ) {
		perror("socket tcp avion");
		return -1;
	}

	/**
	 * Création informations
	 */
	bzero((char *) &target, sizeof(target));
	target.sin_family      = AF_INET;
	target.sin_port        = htons(pPort);
	target.sin_addr.s_addr = inet_addr(pAddr);


	/**
	 * Connexion au server
	 */
	if( connect(*pSocket, (struct sockaddr*) &target, sizeof(struct sockaddr_in)) < 0 ){
		perror("connect avion");
		return -1;
	}


	return 0;

}
