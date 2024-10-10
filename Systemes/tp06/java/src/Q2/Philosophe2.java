package Q2;

public class Philosophe2 extends Thread {

    private static final int N = 20;
    private static Object[] baguettes = new Object[N];
    private final int place;

    static {
        for (int i = 0; i < N; i++) {
            baguettes[i] = new Object();
        }
    }

    public Philosophe2(int place) {
        this.place = place;
    }

    // Odd philosophers take the right chopstick first, even philosophers take the left chopstick first
    public void manger() {
        try {
            if(place % 2 == 0) {
                sleep(100);
                synchronized (baguettes[place]) {
                    System.out.println("Philosophe " + place + " prend la baguette gauche.");
                    sleep(100);
                    synchronized (baguettes[(place + 1) % N]) {
                        System.out.println("Philosophe " + place + " prend la baguette droite.");
                        System.out.println("Philosophe " + place + " mange. MIAM.");
                    }
                }
            } else {
                sleep(100);
                synchronized (baguettes[(place + 1) % N]) {
                    System.out.println("Philosophe " + place + " prend la baguette droite.");
                    sleep(100);
                    synchronized (baguettes[place]) {
                        System.out.println("Philosophe " + place + " prend la baguette gauche.");
                        System.out.println("Philosophe " + place + " mange. MIAM.");
                    }
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
        Philosophe2[] philosophes = new Philosophe2[N];
        for (int i = 0; i < N; i++) {
            philosophes[i] = new Philosophe2(i);
            philosophes[i].start();
        }
    }
}
