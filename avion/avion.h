#ifndef AVION_H
#define AVION_H

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
#include <stdio.h>

#define ALTMAX 20000
#define ALTMIN 0
#define VITMAX 1000
#define VITMIN 200
#define PAUSE 2

struct coordonnees {
  int x;
  int y;
  int altitude;
};

struct deplacement {
  int cap;
  int vitesse;
};
int ouvrir_communication();
void fermer_communication();
void envoyer_caracteristiques();
void initialiser_avion();
void changer_vitesse(int vitesse);
void changer_cap(int cap);
void changer_altitude(int alt);
void afficher_donnees();
void calcul_deplacement();
void se_deplacer();
#endif
