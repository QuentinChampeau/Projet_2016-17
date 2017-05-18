#include "client.h"




int connectTCP(int* pSocket, const char *pAddr, const int pPort){

	/* [0] initialize variables
	=========================================================*/
	struct sockaddr_in target;


	/* [1] Create socket
	=========================================================*/
	*pSocket = socket(AF_INET, SOCK_STREAM, 0);

	if( *pSocket < 0 ) {
		perror("socket tcp avion");
		return -1;
	}

	/* [2] Create @pInfo
	=========================================================*/
	bzero((char *) &target, sizeof(target));
	target.sin_family      = AF_INET;
	target.sin_port        = htons(pPort);
	//memcpy(&target.sin_addr.s_addr, pAddr->h_addr, pAddr->h_length);
	target.sin_addr.s_addr = inet_addr(pAddr);


	/* [3] Connect to server
	=========================================================*/
	if( connect(*pSocket, (struct sockaddr*) &target, sizeof(struct sockaddr_in)) < 0 ){
		perror("connect avion");
		return -1;
	}

	/* [3] Return data
	=========================================================*/
	return 0;


}
