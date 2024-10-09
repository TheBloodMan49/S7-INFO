#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
  FILE* fd = fopen("/tmp/pipe125205567650267", "r");
  char buffer[100];
  while(fgets(buffer, 100, fd)) {
    printf("%s", buffer);
  }
  fclose(fd);
  unlink("/tmp/pipe125205567650267");
  return 0;
}