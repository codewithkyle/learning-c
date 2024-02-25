#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

int main() {
    //                V Sets IPv4
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    //                         ^ Sets TCP

    if (fd == -1) {
        perror("socket");
        return -1;
    }

    printf("%d\n", fd);
}
