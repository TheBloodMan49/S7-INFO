#include "semaphore.h"
#include <stdio.h>

int main() {
  int sem = init_sem(1);
  if(fork() == 0) {
    P(sem);
    printf("Fils: Je suis dans la section critique\n");
    sleep(1);
    printf("Fils: Je sors de la section critique\n");
    V(sem);
  } else {
    P(sem);
    printf("Père: Je suis dans la section critique\n");
    sleep(1);
    printf("Père: Je sors de la section critique\n");
    V(sem);
    wait(NULL); // Attendre le fils si le père est passé en premier
  }
}
