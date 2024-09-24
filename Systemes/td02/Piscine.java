class Piscine {
  int paniers, cabines;

  Object Opaniers, Ocabines;

  Piscine(int k, int n) {
    paniers = k;
    cabines = n;
    Opaniers = new Object();
    Ocabines = new Object();
  }

  void prendrePanier() throws InterruptedException {
    synchronized(Opaniers) {
      while(paniers==0) {
        Opaniers.wait();
      }
      paniers--;
    }
  }

  void rendrePanier() {
    synchronized(Opaniers) {
      Opaniers.notify();
      paniers++;
    }
  }

  void prendreCabine() throws InterruptedException {
    synchronized(Ocabines) {
      while(cabines==0) {
        Ocabines.wait();
      }
      cabines--;
    }
  }

  void rendreCabine() {
    synchronized(Ocabines) {
      Ocabines.notify();
      cabines++;
    }
  }

  public static void main(String[] args) throws InterruptedException {

    Piscine p = new Piscine(8, 2);
    
    // Make a bunch of threads of this
    p.prendrePanier();
    p.prendreCabine();
    // Se changer
    p.rendreCabine();
    // Nager
    p.prendreCabine();
    // Se changer
    p.rendreCabine();
    p.rendrePanier();
  }
}