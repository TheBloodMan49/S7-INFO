package Q2;

public class Philosophe extends Thread {

    private static final int N = 20;
    private static Object[] baguettes = new Object[N];
    private static Object[] table = new Object[N/2];
    private final int id;

    static {
        for (int i = 0; i < N; i++) {
            baguettes[i] = new Object();
        }
        for (int i = 0; i < N/2; i++) {
            table[i] = new Object();
        }
    }

    public Philosophe(int id) {
        this.id = id;
    }

    // We restrict the number of philosophers that can sit at the table at the same time to N/2
    public void manger() {
        int place = id % (N/2);
        synchronized (table[place]) {
            System.out.println("Philosophe " + id + " s'assoit à table.");
            try {
                sleep(100);
                synchronized (baguettes[place]) {
                    System.out.println("Philosophe " + id + " prend la baguette gauche.");
                    sleep(100);
                    synchronized (baguettes[(place + 1) % N]) {
                        System.out.println("Philosophe " + id + " prend la baguette droite.");
                        System.out.println("Philosophe " + id + " mange. MIAM.");
                    }
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public void penser() {
        System.out.println("Philosophe " + id + " pense. Hmmm.");
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
