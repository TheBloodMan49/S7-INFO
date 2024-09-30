package Parking;

import java.util.concurrent.Semaphore;

import static java.lang.Thread.sleep;

public class Parking {

    private static final int MAX_CAPACITY = 10;
    private Semaphore semaphore = new Semaphore(MAX_CAPACITY);

    private final Object monitorNord = new Object();
    private final Object monitorSud = new Object();
    private final Object monitorSortie = new Object();

    public Parking() {
        semaphore = new Semaphore(MAX_CAPACITY);
    }

    public void entreeNord() {
        synchronized (monitorNord) {
            try {
                System.out.println("Je cherche une place entrée Nord !");
                sleep(1000);
                semaphore.acquire();
                System.out.println("J'ai trouvé une place entrée Nord: " + semaphore.availablePermits() + " places disponibles");
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public void entreeSud() {
        synchronized (monitorSud) {
            try {
                System.out.println("Je cherche une place entrée Sud !");
                sleep(1000);
                semaphore.acquire();
                System.out.println("J'ai trouvé une place entrée Sud: " + semaphore.availablePermits() + " places disponibles");
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public void sortie() {
        synchronized (monitorSortie) {
            semaphore.release();
            System.out.println("Je suis sorti: " + semaphore.availablePermits() + " places disponibles");
        }
    }
}
