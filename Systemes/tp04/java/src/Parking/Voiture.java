package Parking;

public class Voiture extends Thread {

    private Parking parking;
    private String entree;

    public Voiture(Parking parking, String entree) {
        this.parking = parking;
        this.entree = entree;
    }

    @Override
    public void run() {
        if(entree.equals("Nord"))
            parking.entreeNord();
        else
            parking.entreeSud();
        try {
            sleep(1000);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        parking.sortie();
    }

    public static void main(String[] args) {
        for(int i = 0; i < 10; i++) {
            Parking parking = new Parking();
            Voiture voitureNord = new Voiture(parking, "Nord");
            Voiture voitureSud = new Voiture(parking, "Sud");
            voitureNord.start();
            voitureSud.start();
        }
    }
}
