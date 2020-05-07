
package java_syst_distrib;

public class Java_Syst_distrib {

    public static Avion avion;
    public static Co_UDP Connexion;
    
    public static void main(String[] args) {
        Connexion = new Co_UDP();
        Connexion.Connexion();
    }
}
