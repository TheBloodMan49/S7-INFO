#include <stdio.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <malloc.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

#define N 200

int shmid;

void fusion(int* tab1, int n1, int* tab2, int n2) {
  int* tab = malloc((n1 + n2) * sizeof(int));
  int i1 = 0;
  int i2 = 0;
  int i = 0;
  while (i1 < n1 && i2 < n2) {
    if (tab1[i1] < tab2[i2]) {
      tab[i] = tab1[i1];
      i1++;
    } else {
      tab[i] = tab2[i2];
      i2++;
    }
    i++;
  }
  while (i1 < n1) {
    tab[i] = tab1[i1];
    i1++;
    i++;
  }
  while (i2 < n2) {
    tab[i] = tab2[i2];
    i2++;
    i++;
  }
  for (int i = 0; i < n1 + n2; i++) {
    tab1[i] = tab[i];
  }
  free(tab);
}

void trifusion(int* tab, int n) {
  if (n > 2) {
    int n1 = n / 2;
    int n2 = n - n1;
    int* tab1 = tab;
    int* tab2 = tab + n1;
    if(fork() == 0) {
      trifusion(tab1, n1);
      exit(0);
    } else if (fork() == 0) {
      trifusion(tab2, n2);
      exit(0);
    } else {
      wait(NULL);
      wait(NULL);
    }
    fusion(tab1, n1, tab2, n2);
  } else if (n == 2) {
    if (tab[0] > tab[1]) {
      int tmp = tab[0];
      tab[0] = tab[1];
      tab[1] = tmp;
    }
  }
}

int compare(const void* a, const void* b) {
  return *(int*)a - *(int*)b;
}

int main(void) {
  srand(time(NULL));
  shmid = shmget(IPC_PRIVATE, sizeof(int)*N, IPC_CREAT | 0666);

  int* tab = shmat(shmid, NULL, 0);
  for (int i = 0; i < N; i++) {
    tab[i] = rand() % N;
  }

  printf("Tableau initial \t: ");
  for(int i = 0; i < N; i++) {
    printf("%d ", tab[i]);
  }
  printf("\n");

  trifusion(tab, N);

  printf("Tableau trié \t\t: ");
  for(int i = 0; i < N; i++) {
    printf("%d ", tab[i]);
  }
  printf("\n");

  qsort(tab, N, sizeof(int), compare);

  printf("Tableau trié (qsort): ");
  for(int i = 0; i < N; i++) {
    printf("%d ", tab[i]);
  }
  printf("\n");

  shmdt(tab);
  shmctl(shmid, IPC_RMID, NULL);
  return 0;
}
