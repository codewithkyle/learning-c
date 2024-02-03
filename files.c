#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // 0 = stdin
    // 1 = stdout
    // 2 = stderr
    
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 0;
    }

    int fd = open(argv[1], O_RDWR | O_CREAT, 0644);
    if (fd == -1)
    {
        perror("open");
        return -1;
    }

    char *mydata = "hi mom!\n";
    write(fd, mydata, strlen(mydata));

    close(fd);

    return 0;
}
