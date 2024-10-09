#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int pipe_fd[2];

int main(int argc, char** argv) {
  if(argc != 2) {
    printf("Give the username as argument");
    exit(1);
  }

  pipe(pipe_fd);

  if (fork()) {
    dup2(pipe_fd[1], STDIN_FILENO);
    close(pipe_fd[0]);
    char* const args[] = {"who", 0};
    execvp("who", args);
  } else {
    dup2(pipe_fd[0], STDOUT_FILENO);
    close(pipe_fd[1]);
    char* const args[] = {"grep", argv[1], 0};
    execvp("grep", args);
  }
}
