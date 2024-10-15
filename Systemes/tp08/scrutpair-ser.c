// TODO : Implement multiplexing with select

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

#include "vb-util.h"

int sock_listen;
char path[UNIX_PATH_MAX];

void handle_term(int sig) {
    close(sock_listen);
    unlink(path);
    kill(0, SIGINT);
    wait(NULL);
    exit(0);
}

int main(int argc, char *argv[]) {

    if(argc != 2) {
        fprintf(stderr, "Usage : %s sock_serveur\n", argv[0]);
        return 1;
    }

    strncpy(path, argv[1], UNIX_PATH_MAX);

    struct sockaddr_un sa;
    sock_listen = vb_create_socket_un(SOCK_STREAM, path, &sa);

    if (sock_listen < 0) {
        perror("vb_create_socket_un");
        return 1;
    }

    signal(SIGTERM, handle_term);

    if (vb_listen(sock_listen, 5) < 0) {
        perror("vb_listen");
        return 1;
    }

    while(1) {
        struct sockaddr_un dist_sa;
        int sock = vb_accept_un(sock_listen, &dist_sa);

        if(fork() == 0) {
            while(1) {
                char buf_recv[1024];
                long n = vb_read(sock, buf_recv, sizeof(buf_recv));
                if(n < 0) {
                    perror("vb_read");
                    close(sock);
                    return 1;
                } else if(n == 0) {
                    fprintf(stderr, "EOF detected\n");
                    close(sock);
                    return 0;
                }

                char buf_send[1024];
                int j = 0;
                for(int i = 0; i < n; i++) {
                    if(buf_recv[i] == '0' ||
                    buf_recv[i] == '2' ||
                    buf_recv[i] == '4' ||
                    buf_recv[i] == '6' ||
                    buf_recv[i] == '8') {
                        buf_send[j] = buf_recv[i];
                        j++;
                    }
                }
                buf_send[j] = '\n';
                buf_send[j+1] = '\0';
                vb_write(sock, buf_send, strlen(buf_send));
            }

        } else {
            close(sock);
            wait(NULL);
        }
    }

}
