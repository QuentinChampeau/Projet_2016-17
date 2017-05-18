

/**
 * Plane -> SGCA
 */
struct avion {
	char num_vol[6]; // 6 bytes
	int  x;           // 4 bytes
	int  y;           // 4 bytes
	int  altitude;    // 4 bytes
	int  cap;         // 4 bytes
	int  vitesse;     // 4 bytes
};


/**
 * SGCA -> viewTerm (si trop chiant, faire une publication periodique multicast)
 */
struct avionS{
	int n;              // 4 byte
	struct avion* data; // 26*[-] bytes
};
/**
 * SGCA -> plane (multicast regulier)
 * SGCA -> viewTerm (apres connexion du viewTerm)
 * SGCA -> ctrlTerm (apres connexion du ctrlTerm)
 */
struct demande_connexion{
	uint32_t ip;   // 4 bytes
	uint16_t port; // 2 bytes
};

/**
 * ctrlTerm -> SGCA -> Plane
 */
struct mise_a_jour{
	char num_vol[6]; // 6 bytes
	char modif_alt;  // 1 byte | vaut 1 si on veut modifier l'altitude
	char modif_cap;  // 1 byte | vaut 1 si on veut modifier le cap
	char modif_vit;  // 1 byte | vaut 1 si on veut modifier le vit
	int  altitude;   // 4 byte
	int  cap;        // 4 byte
	int  vitesse;    // 4 byte
};







/*

// gestion globale
pthread_t mainthreads[4];
char      mainactive[4];

// gestion avions
pthread_t tcpthreads[10];
char      tcpactive[10];

// gestion terminaux visu
pthread_t visuthreads[10];
char      visuactive[10];

void* gererAvion(intptr_t* pParam){
	char a;
	int* socket = (intptr_t) pParam;

	while(){}
		recv(socket, ...);
		storedataFromPlane...
	}


	for( a = 0 ; a < 10 ; a++ )
		if( tcpthreads[a] == pthread_self() )
			tcpactive[a] = 0; // thread libere

	pthread_exit(null);
}



int main(){

	char a, b, c, d, e, f;

	for( a = 0 ; a < 10 ; a++ )
		tcpactive[a] = 0;

	int listenSocket = createTCPServer(ip, port, ..);
	int comSock;


	while(){
		comSock = accept(listenSocket, ...);


		for( a = 0 ; a < 10 ; a++ )
			if( tcpactive[a] == 0 ) // emplacement thread libre
				break;

		// si plus de place
		if( a == 10 )
			break;

		tcpactive[a] = 1; // thread pris
		tcpthread[a] = pthread_create(gererAvion, (void*) &comSock, ...);

	}



	..........



	for( a = 0 ; a < 10 ; a++ )
		pthread_join(tcpthread[a]);

	return EXIT_SUCCESS;
}
*/