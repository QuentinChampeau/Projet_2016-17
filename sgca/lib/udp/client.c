#include "client.h"




int UDPMulticast(int* pSocket, const uint32_t pAddr, const uint16_t pPort, struct sockaddr_in* pInfo){

	/* [0] initialize variables
	=========================================================*/
	int    rtn;
	uint reuse = 1;
	struct ip_mreq mcastReq;


	/* [1] Create socket
	=========================================================*/
	*pSocket = socket(AF_INET, SOCK_DGRAM, 0);

	if( *pSocket < 0 )
		return -1;


	/* [2] Create @pInfo
	=========================================================*/
	pInfo->sin_family      = AF_INET;
	pInfo->sin_port        = htons(pPort);
	pInfo->sin_addr.s_addr = htonl(INADDR_ANY);


	/* [3] Socket opt
	=========================================================*/
	/* 1. Notification d'utilisation multiple du même port */
	if( setsockopt(*pSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(u_int)) < 0 ){
	         close(*pSocket);
	         return -1;
	}


	/* [4] Bind socket
	=========================================================*/
	if( bind(*pSocket, (struct sockaddr*) pInfo, sizeof(struct sockaddr_in)) < 0 ){
	        close(*pSocket);
		return -1;
	}


	/* [5] Ask for mcast group
	=========================================================*/
	mcastReq.imr_multiaddr.s_addr = pAddr;
	mcastReq.imr_interface.s_addr = htonl(INADDR_ANY);

	if( setsockopt(*pSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mcastReq, sizeof(mcastReq)) < 0 ){
		close(*pSocket);
		return -1;
	}

	/* [3] Return data
	=========================================================*/
	return 0;


}
