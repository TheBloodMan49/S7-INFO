#include "controller.h"
#include "semaphore.h"

#define LG_MAX 100
char tp_em[LG_MAX];
int i_em;
int fin_em = init_sem(1);

void tty_em_ligne(char* l) {
  P(fin_em);
  // Recopier l dans tp_em
  ecrire(tp_em[0]);
  i_em = 1;
  demander_it_s();
}

void traitant_it_s() {
  ecrire(tp_em[i_em]);
  if(tp_em[i_em] == '\0') {
    supprimer_it_s();
    V(fin_em);
  } else {
    i_em++;
  }
}

int fin_rec = init_sem(0);
int i_rec;
char tp_rec[LG_MAX];

void tty_rec_ligne(int* lg, char* l) {
  P(fin_rec);
  *lg = i_rec;
  // Recopier tp_rec dans l
  i_rec = 0;
  demander_it_e();
}

void traitant_it_e() {
  lire(&tp_rec[i_rec]);
  if(tp_rec[i_rec] == '\0') {
    supprimer_it_e();
    V(fin_rec);
  } else {
    i_rec++;
  }
}

void tty_init() {
  initialiser();
  demander_it_e();
}
