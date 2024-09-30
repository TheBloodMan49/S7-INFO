#ifndef TP03_SEMAPHORE_H
#define TP03_SEMAPHORE_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>

int init_sem(int val) {
  int sem = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
  if(sem < 0) perror("Error: semget");
  union semun
  {
    int val;
    struct semid_ds *buf;
    ushort *array;
  } arg;
  arg.val = val; // Valeur d'initialisation
  int retval = semctl(sem, 0, SETVAL, arg);
  if(retval < 0) perror("Error: semctl");
  return sem;
}

void P(int sem) {
  struct sembuf op;
  op.sem_num = 0;
  op.sem_op = -1; //1=V, -1=P
  op.sem_flg = 0;
  int retval = semop(sem, &op, 1);
  if(retval != 0) perror("error: semop");
}

void V(int sem) {
  struct sembuf op;
  op.sem_num = 0;
  op.sem_op = 1; //1=V, -1=P
  op.sem_flg = 0;
  int retval = semop(sem, &op, 1);
  if(retval != 0) perror("error: semop");
}

void del_sem(int sem) {
  union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
  } arg;
  int retval = semctl(sem, 0, IPC_RMID, arg);
  if (retval < 0) perror("Error: semctl");
}

#endif //TP03_SEMAPHORE_H
