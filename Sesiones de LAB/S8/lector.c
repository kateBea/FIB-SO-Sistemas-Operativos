#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define STDIN   0
#define STDOUT  1
#define STDERR  2

/*Lee de pipe y escribe por std out todo lo que lee hasta EOF*/
int main(int argc, char** argv)
{
    int ret = close(STDIN);
    if (ret == -1) perror ("__close__ error syscall");
    int fd = open("myPipe", O_RDONLY); //open pipe for read only ops
    if (fd == -1) perror("__open__ error syscall");

    char buffer[256];
    ret = read(fd, buffer, sizeof(buffer));
    if (ret == -1) perror ("__read__ error syscall");
    ret = write(STDOUT, buffer, ret);
    if (ret == -1) perror ("__write__ error syscall");

    return EXIT_SUCCESS;
}