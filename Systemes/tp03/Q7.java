public class Q7 extends Thread{
  private Object synobj;

  public Q7(Object obj) {
    synobj = obj;
  }

  public void run() {
    synchronized(synobj) {
      System.out.println("Début de section critique");
      try {
        sleep(1000);
      } catch(Exception e) {
        System.out.println("Interrupted");
      }
      System.out.println("Fin de section critique");
    }
  }

  public static void main(String[] args) {
    Object synobj = new Object();
    Q7 t1 = new Q7(synobj);
    t1.start();
    Q7 t2 = new Q7(synobj);
    t2.start();
  }
}
