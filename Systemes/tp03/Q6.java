import java.util.concurrent.Semaphore;

public class Q6 extends Thread {
    private Semaphore sem;

    public Q6(Semaphore s) {
        sem = s;
    }

    public void run() {
        try {
            sem.acquire();
            System.out.println("Début de section critique");
            sleep(1000);
            System.out.println("Fin de section critique");
            sem.release();
        } catch(Exception e) {
            System.out.println("error");
        }
    }
    public static void main(String[] args) {
        Semaphore s = new Semaphore(1);

        Q6 t1 = new Q6(s);
        t1.start();
        Q6 t2 = new Q6(s);
        t2.run();
    }
}