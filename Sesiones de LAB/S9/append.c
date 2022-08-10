#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

/*print str to std error and exit program*/
void error_and_exit(const char* str, int ex_code)
{
    perror(str); exit(ex_code);
}

int main(void)
{
    int fd_read = open("file", O_RDONLY, 0);
    if (fd_read < 0) error_and_exit("__open__ error open for read", -1);
    int fd_write = open("file", O_WRONLY, 0);
    if (fd_write < 0) error_and_exit("__open__ error open for write", -1);

    /**
     * off_t lseek(int fd, off_t offset, int whence);
     * SEEK_SET -> The file offset is set to offset bytes.
     * SEEK_CUR -> The file offset is set to its current location plus offset bytes.
     * SEEK_END -> The file offset is set to the size of the file plus offset bytes.
     */
    //opens succesful
    
    //retrieve current end of the file
    //set offset to end of file from where we start writing
    off_t CURRENT_END = lseek(fd_write, 0, SEEK_END);
    if (CURRENT_END < 0) error_and_exit("__lseek__ error lseek current_end", -1);
    
    //init offset pointer to start of the file
    off_t read_offset = lseek(fd_read, 0, SEEK_CUR);
    if (read_offset < 0) 
        error_and_exit("__lseek__ error lseek read_offset", -1);

    char buffer[1]; int ret; 
    ret = read(fd_read, buffer, sizeof(buffer));

    while ((ret > 0) && (read_offset <= CURRENT_END))
    {
        ret = write(fd_write, buffer, ret);
        if (ret < 0) 
            error_and_exit("__write__ error write at line 49", -1);
            
        ret = read(fd_read, buffer, sizeof(buffer));
        if (ret < 0) 
            error_and_exit("__write__ error read at line 51", -1);

        //does not modify file offset just retrieve current position
        read_offset = lseek(fd_read, 0, SEEK_CUR);
        if (read_offset < 0) 
            error_and_exit("__read__ error lseek at line 55", -1);
    }

    if (ret < 0) 
        error_and_exit("__read__ error reading from fd_read file descriptor", -1);
    return EXIT_SUCCESS;
}