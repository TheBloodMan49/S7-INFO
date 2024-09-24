#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>


pid_t pidFils;  

int main(){

  for (int i=0; i<10; i++){
    pidFils= fork();
    if (pidFils!=0){
      /* ------------ code du père ----------------- */
      printf("je suis le pere, mon numero est %d",getpid()); 
      printf(", celui de mon fils est %d\n",pidFils);
    }
    else{
      /* ------------ code du fils ----------------- */
      sleep(1);
      printf("je suis le fils, mon numero est %d",getpid());
      printf(", celui de mon pere est %d\n", getppid());
      sleep(15);
      break;
    }
  }
  sleep(15); // On fait attendre le père
  return 0;

}
