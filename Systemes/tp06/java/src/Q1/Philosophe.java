package Q1;

public class Philosophe extends Thread {

    private static final int N = 20;
    private static Object[] baguettes = new Object[N];
    private final int place;

    static {
        for (int i = 0; i < N; i++) {
            baguettes[i] = new Object();
        }
    }

    public Philosophe(int place) {
        this.place = place;
    }

    public void manger() {
        try {
            sleep(100);
            synchronized (baguettes[place]) {
                System.out.println("Philosophe " + place + " prend la baguette gauche.");
                sleep(100);
                synchronized (baguettes[(place + 1) % N]) {
                    System.out.println("Philosophe " + place + " prend la baguette droite.");
                    System.out.println("Philosophe " + place + " mange. MIAM.");
                }
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void penser() {
        System.out.println("Philosophe " + place + " pense. Hmmm.");
    }

    @Override
    public void run() {
        while (true) {
            manger();
            penser();
        }
    }
    public static void main(String[] args) {
        Philosophe[] philosophes = new Philosophe[N];
        for (int i = 0; i < N; i++) {
            philosophes[i] = new Philosophe(i);
            philosophes[i].start();
        }
    }
}
