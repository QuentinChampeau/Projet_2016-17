#include "server.h"

int connectTCP(int *pSocket, const int pPort) {

	struct sockaddr_in target;

	/**
	 * Création socket
	 */
	*pSocket = socket(AF_INET, SOCK_STREAM, 0);

	if( *pSocket < 0 )
		return -1;

	/**
	 * Création des information
	 */
	bzero((char *) &target, sizeof(target));
	target.sin_family      = AF_INET;
	target.sin_port        = htons(pPort);
	target.sin_addr.s_addr = htonl(INADDR_ANY);

	/**
	 * Bind socket au port
	 */
	if (bind(*pSocket, (struct sockaddr *) &target, sizeof(target)) < 0) {
		perror("bind failed");
		return -1;
	}

	/**
	 * Connexion au client
	 */
	if (listen(*pSocket, 5) < 0) {
		perror("listen");
		return -1;
	}


	return 0;

}