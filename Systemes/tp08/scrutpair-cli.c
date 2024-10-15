#include "vb-util.h"

char path_cli[UNIX_PATH_MAX];
char path_ser[UNIX_PATH_MAX];

void handle_term(int sig) {
    unlink(path_cli);
    exit(0);
}

int main(int argc, char *argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Usage : %s sock_client sock_serveur\n", argv[0]);
        return 1;
    }

    strncpy(path_cli, argv[1], UNIX_PATH_MAX);
    strncpy(path_ser, argv[2], UNIX_PATH_MAX);

    struct sockaddr_un sa_cli;
    int sock_cli = vb_create_socket_un(SOCK_STREAM, path_cli, &sa_cli);

    if (sock_cli < 0) {
        perror("vb_create_socket_un");
        return 1;
    }

    signal(SIGTERM, handle_term);

    struct sockaddr_un sa_ser;
    sa_ser.sun_family = AF_UNIX;
    strncpy(sa_ser.sun_path, path_ser, UNIX_PATH_MAX);

    if (connect(sock_cli, (struct sockaddr *) &sa_ser, sizeof(struct sockaddr_un)) < 0) {
        perror("connect");
        return 1;
    }

    int descriptors[2] = {0, sock_cli};
    fd_set readfds;
    while(1) {
        FD_ZERO(&readfds);
        FD_SET(0, &readfds);
        FD_SET(sock_cli, &readfds);

        int max = sock_cli;
        if(select(max + 1, &readfds, NULL, NULL, NULL) < 0) {
            perror("select");
            close(sock_cli);
            return 1;
        }

        if(FD_ISSET(0, &readfds)) {
            char buf_send[1024];
            printf("Enter a message : ");
            scanf("%s", buf_send);
            vb_write(sock_cli, buf_send, strlen(buf_send));
        }

        if(FD_ISSET(sock_cli, &readfds)) {
            char buf_recv[1024];
            long n = vb_read(sock_cli, buf_recv, sizeof(buf_recv));
            if(n < 0) {
                perror("vb_read");
                close(sock_cli);
                return 1;
            } else if(n == 0) {
                fprintf(stderr, "EOF detected\n");
                close(sock_cli);
                return 0;
            }

            printf("%s", buf_recv);
        }
    }

}