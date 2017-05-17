#ifndef _LIB_TCP_CLIENT_
	#define _LIB_TCP_CLIENT_


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
	int connectTCP(int* pSocket, const uint32_t pAddr, const uint16_t pPort);



#endif
