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
  printf("%d\n", j);

}

int main() {
  action.sa_handler = handler;
  sigaction(SIGINT, &action, NULL);

  for(i = 0; i < 100000000000; i++) {
      if (i % 10000 == 0) {
        j++;
      }
    }

}