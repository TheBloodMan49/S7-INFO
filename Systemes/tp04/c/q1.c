#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include "semaphore.h"

#define N 5
#define ITEMS 20
#define NB_PROD 4
#define NB_CONS 2

int mem;
int sem_data;
int sem_prod;
int sem_cons;

void prod() {
  for(int i = 0; i < ITEMS/NB_PROD; i++) {
    P(sem_prod);
    P(sem_data);
    int *data = shmat(mem, NULL, 0);
    for(int j = 0; j < N; j++) {
      if(data[j] == -1) {
        data[j] = i;
        break;
      }
    }
    shmdt(data);
    V(sem_data);
    V(sem_cons);
  }
}

void cons(int id) {
  for(int i = 0; i < ITEMS/NB_CONS; i++) {
    P(sem_cons);
    P(sem_data);
    int *data = shmat(mem, NULL, 0);
    for(int j = 0; j < N; j++) {
      if(data[j] != -1) {
        printf("Consommateur %d: %d\n", id, data[j]);
        data[j] = -1;
        break;
      }
    }
    shmdt(data);
    V(sem_data);
    V(sem_prod);
  }
}

int main(void) {
  mem = shmget(IPC_PRIVATE, N*sizeof(int), 0666 | IPC_CREAT);

  int *data = shmat(mem, NULL, 0);
  for(int i = 0; i < N; i++) {
    data[i] = -1;
  }

  sem_data = init_sem(1);
  sem_prod = init_sem(N);
  sem_cons = init_sem(0);

  for(int i = 0; i < NB_PROD; i++) {
    if(fork() == 0) {
      prod();
      exit(0);
    }
  }

  for(int i = 0; i < NB_CONS; i++) {
    if(fork() == 0) {
      cons(i);
      exit(0);
    }
  }

  for(int i = 0; i < NB_PROD + NB_CONS; i++) {
    wait(NULL);
  }

  del_sem(sem_data);
  del_sem(sem_prod);
  del_sem(sem_cons);

  shmctl(mem, IPC_RMID, NULL);

  return 0;
}
