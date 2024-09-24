#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <setjmp.h>
#include <unistd.h>
#include <wait.h>
#include <sys/mman.h>

struct sigaction action;
sigset_t mask_nv;
sigset_t mask_anc;

jmp_buf env;

int i;

void handler(int sig){
  sigprocmask(SIG_BLOCK, &mask_nv, &mask_anc);
  i++;
  printf("Signal recu %d\n", i);
  siglongjmp(env,0);
}

int main() {
  sigemptyset(&mask_nv);
  sigaddset(&mask_nv, SIGUSR1);
  sigprocmask(SIG_BLOCK, &mask_nv, &mask_anc);

  action.sa_handler = handler;
  sigaction(SIGUSR1, &action, NULL);

  int pid = fork();
  if (pid == -1) {
    perror("Creation du processus fils echoue");
    exit(0);
  }
  if (pid == 0) {
    setjmp(env);
    sigsuspend(&mask_anc);
  } else {
    for(int i = 0; i < 10000; i++) {
      kill(pid, SIGUSR1);
    }

      wait(NULL);
    }
}