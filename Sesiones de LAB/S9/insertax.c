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

/*print str to std error and exit program*/
void error_and_exit(const char* str, int ex_code)
{
    perror(str); exit(ex_code);
}

int main(void)
{
    int fileHandle = open("salida.txt", O_RDWR, 0);
    if (fileHandle < 0) error_and_exit("__open__ error syscall", -1);

    //retrieve current file offset
    off_t current_offset = lseek(fileHandle, 0, SEEK_END);

    //file has least one character
    if (current_offset != 0) 
    {
        /*shift to avoid overriding character at the last position*/
        char c[1]; current_offset = lseek(fileHandle, -1, SEEK_END);
        int ret = read(fileHandle, c, 1); 
        if (ret < 0) error_and_exit("_read__ error syscall", -1);

        ret = write(fileHandle, c, 1); current_offset = lseek(fileHandle, -2, SEEK_END);
        if (ret < 0) error_and_exit("__write__ error syscall", -1);
    }

    //No shift if file is empty
    write(fileHandle, "X", 1);
    return EXIT_SUCCESS;
}