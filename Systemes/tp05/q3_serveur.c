#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <setjmp.h>
#include <fcntl.h>

int fd;

struct sigaction action_USR1;
struct sigaction action_USR2;
struct sigaction action_TERM;

void service1() {
  write(fd, "JE SUIS LE SERVICE 1 !!!!!\n", 27);
}

void service2() {
  write(fd, "Je suis le service 2 >_<\n", 25);
}

void handle_USR1(int sig) {
  service1();
}

void handle_USR2(int sig) {
  service2();
}

void handle_TERM(int sig) {
  close(fd);
  unlink("/tmp/pipe");
  exit(0);
}

int main(void) {
  // Handle usr1 and usr2 signals
  action_USR1.sa_handler = handle_USR1;
  sigaction(SIGUSR1, &action_USR1, NULL);
  action_USR2.sa_handler = handle_USR2;
  sigaction(SIGUSR2, &action_USR2, NULL);

  action_TERM.sa_handler = handle_TERM;
  sigaction(SIGTERM, &action_TERM, NULL);


  printf("PID serveur : %d\n", getpid());
  mkfifo("/tmp/pipe", 0666);
  fd = open("/tmp/pipe", O_WRONLY);

  char buffer[100];
  sprintf(buffer, "%d", getpid());

  while(1) {
    write(fd, buffer, 100);
    printf("PID du serveur envoyé\n");

    pause();
  }
}