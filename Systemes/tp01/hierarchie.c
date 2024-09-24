#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

pid_t pidFils;
int generation;

int main(){
  generation = 1;

  int pids[5];
  pids[0] = getppid();
  pids[1] = getpid();

  for (int i=0; i<2; i++){
    
    pidFils= fork();
    
    if (pidFils!=0){
      /* ------------ code du père ----------------- */
      // printf("je suis le pere, mon numero est %d",getpid()); 
      // printf(", celui de mon fils est %d\n",pidFils);
    }
    else{
      /* ------------ code du fils ----------------- */
      i = -1;
      generation++;
      pids[generation] = getpid();
      printf("je suis le fils, mon numero est %d",getpid());
      printf(", mes ancetres sont : ");
      for (int j = 0; j < generation; j++){
        printf("%d ", pids[j]);
      }
      if (generation == 4) break;
    }
  }
  pause(); // On fait attendre le père
  return 0;

}
