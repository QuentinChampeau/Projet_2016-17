package java_syst_distrib;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.SocketException;
import java.nio.ByteBuffer;


/**
 *
 * @author Jérémi Quentin
 */
public class Co_UDP {
	public final static int port = 2345;
    	//Avion[] avion;
	ByteBuffer B;
	int nbAvion,i,n;
	String[] S;

	/**
	 * Crée la connexion avec le SGCA pour recevoir les coordonnées des avions
	 * @param
	 * @return 
	 */
	public void Connexion() {
		System.out.println("Connexion...");
		try {
            // Création de la connexion côté serveur, en spécifiant un port d'écoute
            // DatagramSocket server = new DatagramSocket(port);
			InetAddress group = InetAddress.getByName("224.0.0.1");
			MulticastSocket s = new MulticastSocket(port);
			s.joinGroup(group);


			while(true) {

                // On s'occupe maintenant de l'objet paquet
				byte[] buffer = new byte[8000];
                // byte rawCode[] = new byte[5];
				DatagramPacket packet = new DatagramPacket(buffer, buffer.length);

                // Cette méthode permet de récupérer le datagramme envoyé par le client
                // Elle bloque le thread jusqu'à ce que celui-ci ait reçu quelque chose.
				s.receive(packet);

				String chaine = new String(packet.getData());
                /*B = ByteBuffer.wrap(packet.getData());
                nbAvion=B.getInt();
                System.out.println(nbAvion);*/
				// s.receive( packet ) ;
                S = chaine.split("/");
                nbAvion = Integer.parseInt(S[0]);

                Avion avion[] = new Avion[nbAvion];
                for (i = 0; i < nbAvion; i++) {
                	avion[i] = new Avion();
                }

                n = 0;

                for (i = 0; i < nbAvion; i++) {
                	avion[i].setId(S[1+n]);
                	avion[i].setX(Integer.parseInt(S[2+n]));
                	avion[i].setY(Integer.parseInt(S[3+n]));
                	avion[i].setAltitude(Integer.parseInt(S[4+n]));
                	avion[i].setCap(Integer.parseInt(S[5+n]));
                	avion[i].setVitesse(Integer.parseInt(S[6+n]));
                	n=n+6;
					/*B.get(rawCode, 0, 6);
					avion[i].setId(new String(rawCode));
					avion[i].setX(B.getInt());
					avion[i].setY(B.getInt());
					avion[i].setAltitude(B.getInt());
					avion[i].setCap(B.getInt());
					avion[i].setVitesse(B.getInt());*/
				}
				/**
				 * Commande pour clean l'écran
				 */
				System.out.print("\033[H\033[2J");

				System.out.println("LE NOMBRE D'AVION EST DE " + nbAvion);

				for (i=0;i<nbAvion;i++){
					Affiche(avion[i]);
				}

                //On réinitialise la taille du datagramme, pour les futures réceptions
		      	packet.setLength(buffer.length);
		  	}
		} catch (SocketException e) {
			e.printStackTrace();
		} catch (IOException e) {
                   //TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
        
	/**
	 * Affiche les coordonnées des avions
	 * @param avion contient toutes les informations à savoir sur l'avion
	 * @return 
	 */
	public void Affiche(Avion avion) {
		System.out.println("*************************");
		System.out.println("** Console d'affichage **");
		System.out.println("*************************");
		System.out.println("** ID de l'avion : " + avion.getId());
		System.out.println("** Coordonnée :");
		System.out.println("**\t-X : " + avion.getX());
		System.out.println("**\t-Y : " + avion.getY());
		System.out.println("**");
		System.out.println("** Altitude : " + avion.getAltitude());
		System.out.println("** Cap : " + avion.getCap());
		System.out.println("** Vitesse : " + avion.getVitesse());
	}
}
