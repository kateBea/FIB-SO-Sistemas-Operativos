#include <sys/wait.h>
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

const char* init = "Inicio\n";
const char* end  = "Fin\n";

int main(int argc, char** argv)
{
    int _pipe[2];
    int ret;
    
    //pipefd[0] refers to the read end of the pipe
    //pipefd[1] refers to the write end of the pipe.

    ret = pipe(_pipe);
    if (ret == - 1) perror("__pipe__ error syscall");

    ret = fork();
    if (ret == -1) perror("__fork__ error syscal");

    if (ret == 0) 
    {
        /*CHILD CODE*/
        
        close(STDIN);       //close 0 FD to dup _pipe[0] to it
        close (_pipe[1]);   //child does not write to pipe, close to avoid blocking
        dup(_pipe[0]);
        execlp("cat", "cat", (char*)NULL);
    }
    else 
    {
        /*PARENT CODE*/
        
        close(_pipe[0]);    //parent does not read from pipe  
        write(_pipe[1], init, strlen(init));
        close(_pipe[1]);    //close _pipe writ end point to avoid blocking child
        waitpid(-1, NULL, 0);
        write(STDOUT, end, strlen(end));
    }


}