#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include "semaphore.h"

#define NB_RED 2
#define NB_LEC 5

int sem_lec;
int mutex;

int lec;

void lecteur(int id) {
  P(sem_lec);
  int* nblec = shmat(lec, NULL, 0);
  if(*nblec == 0) P(mutex);
  *nblec++;
  shmdt(nblec);
  V(sem_lec);
  printf("Lecteur %d: lecture\n", id);
  sleep(1);
  P(sem_lec);

  nblec = shmat(lec, NULL, 0);
  if(*nblec == 1) V(mutex);
  *nblec--;
  shmdt(nblec);
  V(sem_lec);
}

void redacteur(int id) {
  P(mutex);
  printf("Redacteur %d: ecriture\n", id);
  sleep(1);
  V(mutex);
}

int main(void) {
  sem_lec = init_sem(1);
  mutex = init_sem(1);

  lec = shmget(IPC_PRIVATE, sizeof(int), 0666 | IPC_CREAT);

  for(int i = 0; i < NB_RED; i++) {
    if(fork() == 0) {
      redacteur(i);
      exit(0);
    }
  }

  for(int i = 0; i < NB_LEC; i++) {
    if(fork() == 0) {
      lecteur(i);
      exit(0);
    }
  }

  for(int i = 0; i < NB_RED + NB_LEC; i++) {
    wait(NULL);
  }

  del_sem(sem_lec);
  del_sem(mutex);

  return 0;
}
