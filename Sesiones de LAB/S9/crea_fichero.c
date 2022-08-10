#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define STDOUT  1
#define STDIN   0
#define STERR   2
#define RW_______ 0600

/*print str to std error and exit program*/
void error_and_exit(const char* str, int ex_code)
{
    perror(str); exit(ex_code);
}

int main(void)
{
    int fileHandle = creat("salida.txt", S_IWUSR | S_IRUSR);
    if (fileHandle < 0) error_and_exit("__creat__ error syscall", -1);
    write(fileHandle, "ABCD", 4);
    return EXIT_SUCCESS;
}