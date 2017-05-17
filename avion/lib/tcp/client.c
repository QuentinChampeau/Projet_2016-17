#include "client.h"




int connectTCP(int* pSocket, const uint32_t pAddr, const uint16_t pPort){

	/* [0] initialize variables
	=========================================================*/
	struct sockaddr_in* target;
	

	/* [1] Create socket
	=========================================================*/
	*pSocket = socket(AF_INET, SOCK_STREAM, 0);

	if( *pSocket < 0 )
		return -1;


	/* [2] Create @pInfo
	=========================================================*/
	target->sin_family      = AF_INET;
	target->sin_port        = htons(pPort);
	target->sin_addr.s_addr = htonl(pAddr);


	/* [3] Connect to server
	=========================================================*/
	if( connect(*pSocket, (struct sockaddr*) target, sizeof(struct sockaddr_in)) < 0 )
		return -1;


	/* [3] Return data
	=========================================================*/
	return 0;


}
