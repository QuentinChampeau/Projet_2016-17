#ifndef _STUB_H_
	#define _STUB_H_
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
 * SGCA -> viewTerm
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

#endif
