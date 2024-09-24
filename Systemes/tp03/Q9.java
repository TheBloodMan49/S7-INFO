import java.util.Queue;
import java.util.LinkedList;

public class Q9 extends Thread{
  private Semaphore sem;
  private String id;

    public Q9(Semaphore s, String i) {
        sem = s;
        id = i;
    }

    public void run() {
        try {
            sem.P();
            System.out.println("[Thread "+id+"] Début de section critique");
            sleep(1000);
            System.out.println("[Thread "+id+"] Fin de section critique");
            sem.V();
        } catch(Exception e) {
            System.out.println(e.getMessage());
        }
    }
    public static void main(String[] args) {
        Semaphore s = new Semaphore();
        s.init(1);

        Q9 t1 = new Q9(s, "1");
        t1.start();
        Q9 t2 = new Q9(s, "2");
        t2.start();
        Q9 t3 = new Q9(s, "3");
        t3.start();
    }
}

class Semaphore {
  private int counter;
  private Queue<Object> waiting;

  public Semaphore() {
    counter = 0;
    waiting = new LinkedList<>();
  }

  public synchronized void init(int value) {
    counter = value;
  }

  public synchronized void P() throws InterruptedException {
      Object seat = new Object();
      waiting.add(seat);
    while(counter == 0 || waiting.peek() != seat) {
      wait();
    }
    waiting.remove(seat);
    counter--;
  }

  public synchronized void V() {
    notify();
    counter++;
  }
}
