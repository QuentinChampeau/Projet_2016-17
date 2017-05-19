package java_syst_distrib;


public class Avion {
    public Avion() {}
    int x, y, altitude, cap, vitesse;
    String id;

    /**
     * setter X
     * @param x la coordonnée x à ajouter à l'avion
     * @return
     */
    public void setX(int x) {
        this.x = x;
    }
    /**
     * setter y
     * @param y la coordonnée y à ajouter à l'avion
     * @return
     */
    public void setY(int y) {
        this.y = y;
    }
    /**
     * setter altitude
     * @param altitude la coordonnée altitude à ajouter à l'avion
     * @return
     */
    public void setAltitude(int altitude) {
        this.altitude = altitude;
    }
    /**
     * setter cap
     * @param cap la coordonnée cap à ajouter à l'avion
     * @return
     */
    public void setCap(int cap) {
        this.cap = cap;
    }
    /**
     * setter vitesse
     * @param vitesse la coordonnée vitesse à ajouter à l'avion
     * @return
     */
    public void setVitesse(int vitesse) {
        this.vitesse = vitesse;
    }
    /**
     * getter x
     * @param 
     * @return la coordonnée x de l'avion
     */
    public int getX() {
        return x;
    }
    /**
     * getter y
     * @param 
     * @return la coordonnée y de l'avion
     */
    public int getY() {
        return y;
    }
    /**
     * getter altitude
     * @param 
     * @return la coordonnée altitude de l'avion
     */
    public int getAltitude() {
        return altitude;
    }
    /**
     * getter cap
     * @param 
     * @return la coordonnée cap de l'avion
     */
    public int getCap() {
        return cap;
    }
    /**
     * getter vitesse
     * @param 
     * @return la coordonnée vitesse de l'avion
     */
    public int getVitesse() {
        return vitesse;
    }
    
    
    
    /**
     * getter id
     * @param 
     * @return la coordonnée id de l'avion
     */
    public String getId() {
        return id;
    }
    /**
     * setter id
     * @param id la coordonnée id à ajouter à l'avion
     * @return
     */
    public void setId(String id) {
        this.id = id;
    }

}
