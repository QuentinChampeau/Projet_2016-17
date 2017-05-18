#include "server.h"


int UDPMulticast(int* pSocket, const char *pAddr, const uint16_t pPort, struct sockaddr_in* pInfo){


	uint reuse = 1;
	struct ip_mreq mcastReq;

	memset(pInfo, 0, sizeof(struct sockaddr_in));
	memset(&mcastReq, 0, sizeof(struct ip_mreq));

	/**
	 * Création de la socket
	 */
	*pSocket = socket(AF_INET, SOCK_DGRAM, 0);

	if( *pSocket < 0 ) {
		perror("socket server avion");
		return -1;
	}

	/**
	 * Notification d'utilisation multiple du même port
	 */
	if( setsockopt(*pSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(u_int)) < 0 ){
		perror("setsockopt server avion");
		close(*pSocket);
		return -1;
	}
	/**
	 * Création informations
	 */
	pInfo->sin_family      = AF_INET;
	pInfo->sin_port        = htons(pPort);
	pInfo->sin_addr.s_addr = htonl(INADDR_ANY);


	/**
	 * Bind socket
	 */
	if( bind(*pSocket, (struct sockaddr*) pInfo, sizeof(struct sockaddr_in)) < 0 ){
        perror("bind server avion");
        close(*pSocket);
		return -1;
	}


	/**
	 * Demande de groupe mcast
	 */
	mcastReq.imr_multiaddr.s_addr = inet_addr(pAddr);
	mcastReq.imr_interface.s_addr = htonl(INADDR_ANY);

	/**
	 * JOIN multicast group on default interface
	 */
	if( setsockopt(*pSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mcastReq, sizeof(mcastReq)) < 0 ) {
		perror("setsockopt server avion");
		close(*pSocket);
		return -1;
	}


	return 0;

}
