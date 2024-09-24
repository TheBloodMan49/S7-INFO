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

int i,j;

void handler(int sig){
  j++;
  longjmp(env,0);
}

int main() {

  int pid = fork();
  if (pid == -1) {
    perror("Creation du processus fils echoue");
    exit(0);
  }
  if (pid == 0) {
    int ppid = getppid();
    for(i = 0; i < 100000000; i++) {
      if (i % 10000 == 0) {
        kill(ppid, SIGUSR1);
      }
    }
  } else {
    action.sa_handler = handler;
    sigaction(SIGUSR1, &action, NULL);
    sigemptyset(&mask_nv);
    sigaddset(&mask_nv, SIGUSR1);
    sigprocmask(SIG_BLOCK, &mask_nv, &mask_anc);
    setjmp(env);
    printf("j = %d\n", j);
    sigsuspend(&mask_anc);
    wait(NULL);
  }
}