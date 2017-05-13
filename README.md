# Projet_2016-17
#http://www.csd.uoc.gr/~hy556/material/tutorials/cs556-3rd-tutorial.pdf
#L'avion doit recevoir les données pour se connecter à du TCP via le multicast du SGCA
#Une fois fait il envoie ses données de navigation via socket TCP

Avion:
- multicast :
  + port multicast (de 1024 à 65535)
  + IP multicast (de 224.0.0.0 à 239.255.255.255)
  + socket        [socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP /* ou 0 */)]:
    -- setsockopt [setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *) &reuse, sizeof(reuse))]
    -- bind       [bind(sock, (struct sockaddr *) &addr_avion, sizeof(addr_avion)]
    -- sockopt    [setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq,sizeof(mreq)]
  + recvfrom      [recvfrom(sock, &addr_SGCA, sizeof(addr_SGCA), 0, (struct sockaddr *) &addr_envoyeur, (socklen_t *) &addrlen)]
  
 - TCP :
  + IP serveur donnée par le sockaddr_in envoyé par le multicast
  + port
  + socket                              [socket(AF_INET, SOCK_STREAM, 0);]
  + connecter la socket à la connexion  [connect(sock, (struct sockaddr *) &addr_SGCA, sizeof(addr_SGCA))]
  + setsockopt [setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char *)&value, sizeof(int))]
  + send [send(sock, (char*)&message, sizeof(message), 0) != sizeof(message)]
