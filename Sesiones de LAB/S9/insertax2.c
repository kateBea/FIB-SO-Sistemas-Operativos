#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFF_LIMIT   512

/*print str to std error and exit program*/
void error_and_exit(const char* str, int ex_code)
{
    perror(str); exit(ex_code);
}

/*program usage*/
void usage(void)
{
    char buffer[128];
    strcpy(buffer, "usage: prog [OFFSET] [FILE] [BYTE]... OFFSET in [0, file_size)\n");
    write (STDOUT_FILENO, buffer, strlen(buffer));
    strcpy(buffer, "insert [BYTE] at position indicated by OFFSET\n");
    write (STDOUT_FILENO, buffer, strlen(buffer));
    exit(EXIT_SUCCESS);
}

/*shift content from fileHandle towards the end*/
void shift(int offset, const char* file_name)
{
    int fileHandle, ret, counter, limit, num_loops;
    off_t orig_eof, temp;
    char buffer[BUFF_LIMIT];
    bool fits_on_buffer;

    if ((fileHandle = open(file_name, O_RDWR, 0)) < 0) 
        error_and_exit("__open__ error in fuction shift", -1);

    /*rtrieve current file max size*/
    orig_eof = lseek(fileHandle, 0, SEEK_END);

    
    /*first read bytes fit on the buffer*/
    fits_on_buffer = (orig_eof-offset) <= BUFF_LIMIT;
    if (fits_on_buffer) lseek(fileHandle, offset, SEEK_SET);
    else                lseek(fileHandle, orig_eof-BUFF_LIMIT, SEEK_SET);

    ret = read(fileHandle, buffer, sizeof(buffer));
    counter = BUFF_LIMIT;

    /*num loops increases by 1 every time we read BUFF_LIMIT bytes*/
    int iter = 0;
    num_loops = ((orig_eof - offset)/BUFF_LIMIT) + 1;

    while ((ret > 0) && (iter < num_loops))
    {   
        if ((orig_eof-counter) < offset)   
        {
            temp = offset;
            limit = (orig_eof-counter+BUFF_LIMIT) - offset;
        }
        else
        {
            temp = orig_eof-counter;
            limit = BUFF_LIMIT;
        }                                

        lseek(fileHandle, temp+1, SEEK_SET);
        write(fileHandle, buffer, limit);
        counter = counter + BUFF_LIMIT;

        if ((orig_eof-counter) < offset)   
        {
            temp = offset;
            limit = (orig_eof-counter+BUFF_LIMIT) - offset;
        }
        else
        {
            temp = orig_eof-counter;
            limit = BUFF_LIMIT;
        } 
        lseek(fileHandle, temp, SEEK_SET);
        ret = read(fileHandle, buffer, limit);

        ++iter;
    }
    close (fileHandle);
}

int main(int argc, char **argv)
{
    int offset;  
    int fileHandle;
    char buffer[BUFF_LIMIT];

    if (argc != 4) usage();

    if ((fileHandle = open(argv[2], O_WRONLY, 0)) < 0) 
        error_and_exit("__open__ error in main", -1);
    offset = atoi(argv[1]);


    //retrieve current file size
    off_t upper_bound = lseek(fileHandle, 0, SEEK_END);
    
    if (! (offset > -1 && offset < upper_bound))
    {
        strcpy(buffer, "file OFFSET not valid\n");
        write (STDOUT_FILENO, buffer, strlen(buffer));
        sprintf(buffer, "file OFFSET between 0 and %li (both included)\n", upper_bound-1);
        write (STDOUT_FILENO, buffer, strlen(buffer));
        exit(EXIT_SUCCESS);
    }
    
    shift(offset, argv[2]);
    lseek(fileHandle, offset, SEEK_SET);
    write(fileHandle, argv[3], 1);

//FOR DEBUG PURPOSES
#ifdef _DEBUG
    //cat the modified file
    pid_t pid = fork();
    if (pid < 0) error_and_exit("__fork__ error", -1);
    if (pid == 0)
    {
        execlp("cat", "cat", argv[2], (char*)NULL);
        error_and_exit("__execlp__ error", -1);
    }
    
    waitpid(-1, NULL, 0);
#endif

    return EXIT_SUCCESS;
}
