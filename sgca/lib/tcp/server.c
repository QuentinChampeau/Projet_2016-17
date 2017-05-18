#include "server.h"

int connectTCP(int *pSocket, const char *pAddr, const int pPort) {

	/* [0] initialize variables
	=========================================================*/
	struct sockaddr_in target;

	//memset(target, 0, sizeof(struct sockaddr_in));
	/* [1] Create socket
	=========================================================*/
	*pSocket = socket(AF_INET, SOCK_STREAM, 0);

	if( *pSocket < 0 )
		return -1;

	/* [2] Create @pInfo
	=========================================================*/
	bzero((char *) &target, sizeof(target));
	target.sin_family      = AF_INET;
	target.sin_port        = htons(pPort);
	target.sin_addr.s_addr = htonl(INADDR_ANY/*pAddr*/);

	if (bind(*pSocket, (struct sockaddr *) &target, sizeof(target)) < 0) {
		perror("bind failed");
		return -1;
	}
	printf("bind fait\n");
	/* [3] Connect to server
	=========================================================*/
	if (listen(*pSocket, 5) < 0) {
		perror("listen");
		return -1;
	}


	/* [3] Return data
	=========================================================*/
	return 0;


}