#ifndef _LIB_UDP_SERVER_
	#define _LIB_UDP_SERVER_


#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>

	int UDPMulticast(int* pSocket, const char *pAddr, const uint16_t pPort, struct sockaddr_in* pInfo);



#endif
