#include "server.h"

int connectTCP(int *pSocket, const int pPort) {

	struct sockaddr_in target;
	 int reuse = 1;

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


	if (setsockopt(*pSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
		perror("setsockopt reusse");
		return -1;
	}
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