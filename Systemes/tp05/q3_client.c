#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>

int main(void) {
  int fd = open("/tmp/pipe", O_RDONLY);

  char buffer[100];
  read(fd, buffer, 100);
  printf("%s\n", buffer);

  int pid = (int) strtol(buffer, NULL, 10);

  printf("PID du serveur : %d\n", pid);
  printf("Entrez 1 pour demander le service 1, 2 pour le service 2 : ");
  scanf("%s", buffer);

  if(buffer[0] == '1') {
    kill(pid, SIGUSR1);
  } else if(buffer[0] == '2') {
    kill(pid, SIGUSR2);
  } else {
    printf("Mauvaise commande\n");
  }

  read(fd, buffer, 100);
  printf("%s", buffer);

  close(fd);
  return 0;
}