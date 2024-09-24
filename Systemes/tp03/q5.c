#include "semaphore.h"
#include <stdio.h>

int main() {
  int P1 = init_sem(2);
  int P2 = init_sem(0);
  int P3 = init_sem(0);

  if(fork()==0) {
    if(fork()==0) {
      while(1) {
        P(P2);
        printf("C");
        fflush(stdout);
        //sleep(1);
        V(P1);
      }
    } else {
    while(1) {
      P(P3);
      printf("B");
      fflush(stdout);
      //sleep(1);
      V(P1);
    }
    }
  } else {
    while(1) {
      P(P1);
      P(P1);
      printf("A");
      fflush(stdout);
      //sleep(1);
      V(P2);
      V(P3);
    }
  }
}