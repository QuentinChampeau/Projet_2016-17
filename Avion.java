package java_syst_distrib;


public class Avion {
    public Avion(){}
    int x, y, altitude,cap,vitesse;
    String id;

    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
    }

    public void setAltitude(int altitude) {
        this.altitude = altitude;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public int getAltitude() {
        return altitude;
    }

    public void setCap(int cap) {
        this.cap = cap;
    }

    public void setVitesse(int vitesse) {
        this.vitesse = vitesse;
    }

    public int getCap() {
        return cap;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public int getVitesse() {
        return vitesse;
    }
}
