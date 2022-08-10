#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define STDIN   0
#define STDOUT  1
#define STDERR  2

const char* str1 = "No process has opened FIFO for read operation\n";
const char* str2 = "Process reader found\n";

/*Lee de entrada std hasta que haya EOF y escribe a pipe*/
int main(int argc, char** argv)
{
    dev_t dev_spec = 0;
    int ret = mknod("myPipe", S_IFIFO, dev_spec);

    if (ret == -1) perror ("__mknod__ error syscall");

    ret = close(STDOUT);
    if (ret == -1) perror ("__close__ error syscall");
    int fd = open("myPipe", O_NONBLOCK | O_WRONLY);     //open pipe for write only ops
    if ((fd == -1) && (errno == ENXIO)) write(STDERR, str1, strlen(str1));
    while ((fd == -1) && (errno == ENXIO))
    {
        fd = open("myPipe", O_NONBLOCK | O_WRONLY);
    }
    write(STDERR, str2, strlen(str2));
    
    if (fd == -1) perror("__open__ error syscall");

    char buffer[256];
    ret = read(STDIN, buffer, sizeof(buffer));
    if (ret == -1) perror ("__read__ error syscall");
    ret = write(fd, buffer, ret);
    if (ret == -1) perror ("__write__ error syscall");

    return EXIT_SUCCESS;
}