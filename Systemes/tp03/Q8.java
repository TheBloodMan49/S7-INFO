public class Q8 extends Thread{
  private Semaphore sem;

    public Q8(Semaphore s) {
        sem = s;
    }

    public void run() {
        try {
            sem.P();
            System.out.println("Début de section critique");
            sleep(1000);
            System.out.println("Fin de section critique");
            sem.V();
        } catch(Exception e) {
            System.out.println(e.getMessage());
        }
    }
    public static void main(String[] args) {
        Semaphore s = new Semaphore();
        s.init(1);

        Q8 t1 = new Q8(s);
        t1.start();
        Q8 t2 = new Q8(s);
        t2.run();
    }
}

class Semaphore {
  private int counter;

  public Semaphore() {
    counter = 0;
  }

  public synchronized void init(int value) {
    counter = value;
  }

  public synchronized void P() throws InterruptedException {
      while(counter == 0) {
          wait();
      }
      counter--;
  }

  public synchronized void V() {
      notify();
      counter++;
  }
}
