#include "serveur.h"

int connectTCP(int *pSocket, const uint32_t pAddr, const uint16_t pPort) {

	/* [0] initialize variables
	=========================================================*/
	struct sockaddr_in* target;

	memset(&target, 0, sizeof(server));
	/* [1] Create socket
	=========================================================*/
	*pSocket = socket(AF_INET, SOCK_STREAM, 0);

	if( *pSocket < 0 )
		return -1;


	/* [2] Create @pInfo
	=========================================================*/
	target->sin_family      = AF_INET;
	target->sin_port        = htons(pPort);
	target->sin_addr.s_addr = htonl(INADDR_ANY/*pAddr*/);


	if (bind(*pSocket, (struct sockaddr *) target, sizeof(*target)) < 0) {
		perror("bind failed\n");
		return -1;
	}

	/* [3] Connect to server
	=========================================================*/
	if (listen(*pSocket, 5) < 0) {
		perror("listen\n");
		return -1;
	}


	if( accept(*pSocket, (struct sockaddr*) target, sizeof(struct sockaddr_in)) < 0 ) {
		perror("accept serveur");
		return -1;
	}


	/* [3] Return data
	=========================================================*/
	return 0;


}