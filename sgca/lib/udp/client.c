#include "client.h"




int UDPMulticast(int* pSocket, const char *pAddr, const uint16_t pPort, struct sockaddr_in* pInfo){

	uint reuse = 1;
	struct ip_mreq mcastReq;
  	unsigned char mc_ttl=1;     /* time to live (hop count) */

	memset(pInfo, 0, sizeof(struct sockaddr_in));

	/* création socket */
	*pSocket = socket(AF_INET, SOCK_DGRAM, 0);

	if( *pSocket < 0 ){
		perror("création socket");
		return -1;
	}

	/**
	 * Set the TTL (time to live/hop count) for the send
	 */
	if ((setsockopt(*pSocket, IPPROTO_IP, IP_MULTICAST_TTL, (void*) &mc_ttl, sizeof(mc_ttl))) < 0) {
		perror("setsockopt() failed");
		return -1;
	}

	/**
	 * saisie données
	 */
	pInfo->sin_family      = AF_INET;
	pInfo->sin_port        = htons(pPort);
	pInfo->sin_addr.s_addr = inet_addr(pAddr);


	/**
	 * Notification d'utilisation multiple du même port
	 */
	if( setsockopt(*pSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(u_int)) < 0 ){
		perror("setsockopt");
		close(*pSocket);
		return -1;
	}


	/**
	 * Ask for mcast group
	 */
	mcastReq.imr_multiaddr.s_addr = inet_addr(pAddr);
	mcastReq.imr_interface.s_addr = htonl(INADDR_ANY);

	if( setsockopt(*pSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mcastReq, sizeof(mcastReq)) < 0 ){
		perror("setsockopt");
		close(*pSocket);
		return -1;
	}


	return 0;


}
