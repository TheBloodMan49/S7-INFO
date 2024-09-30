#include "controller.h"

void tty_init() {
  initialiser();
}

void tty_em_ligne(char* l) {
  int c = 0;
  do {
    while(!etat_sortie);
    ecrire(l[c]);
  } while(l[c++] != '\0');
}

void tty_rec_ligne(int* lg, char* l) {
  char fin_ligne = 0;
  *lg = 0;
  while(!fin_ligne) {
    while(!etat_entree);
    lire(l + *lg);
    if(l[*lg] == '\0')
      fin_ligne = 1;
    (*lg)++;
  }
}
