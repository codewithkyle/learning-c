#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef enum {
    PROTO_HELLO,
} proto_type_e;

typedef struct {
    proto_type_e type;
    unsigned short len;
} proto_hdr_t;

void handle_client(int fd) {
    char buf[4096] = {0};
    proto_hdr_t *hdr = (proto_hdr_t*)buf;

    hdr->type = htonl(PROTO_HELLO);
    hdr->len = sizeof(int);
    int reallen = hdr->len;
    hdr->len = htons(hdr->len);

    int *data = &hdr[1];
    *data = htonl(1);

    write(fd, hdr, sizeof(proto_hdr_t) + reallen);
}

int main() {
    struct sockaddr_in clientInfo = {0};
    uint clientSize = 0;

    struct sockaddr_in serverInfo = {0};
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_addr.s_addr = 0;
    serverInfo.sin_port = htons(5555);

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    //                ^        ^ Sets TCP
    //                ^ Sets IPv4

    if (fd == -1) {
        perror("socket");
        return -1;
    }

    // bind socket
    if (bind(fd, (struct sockaddr*)&serverInfo, sizeof(serverInfo)) == -1) {
        perror("bind");
        close(fd);
        return -1;
    }

    // listen
    if (listen(fd, 0) == -1) {
        perror("listen");
        close(fd);
        return -1;
    }

    // accept
    while (1){
        int cfd = accept(fd, (struct sockaddr*)&clientInfo, &clientSize);
        if (cfd == -1){
            perror("accept");
            close(fd);
            return -1;
        }

        handle_client(cfd);

        close(cfd);
    }

}
