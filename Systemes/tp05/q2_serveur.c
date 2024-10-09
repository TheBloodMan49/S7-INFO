#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
  printf("PID serveur : %d\n", getpid());
  mkfifo("/tmp/pipe125205567650267", 0666);
  FILE* fd = fopen("/tmp/pipe125205567650267", "w");

  fprintf(fd, "Hello, world!\n");
  fclose(fd);
  return 0;
}
