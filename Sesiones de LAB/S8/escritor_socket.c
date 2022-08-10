#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <socketMng.h>

#define STDIN   0
#define STDOUT  1
#define STDERR  2

/*usage of program*/
void usage(void)
{
    char buffer[128];
    sprintf(buffer, "usage: escritor_socket [socket]\n");
    write(STDERR, buffer, strlen(buffer));
    sprintf(buffer, "This program requests connection to socket specified in argv[1]\n");
    write(STDERR, buffer, strlen(buffer));
    sprintf(buffer, "[socket] may be the address of the socket itself\n");
    write(STDERR, buffer, strlen(buffer));
    exit(EXIT_FAILURE);
}

void error_exit(const char* str, int exit_code)
{
    perror(str);
    exit(exit_code);
}

/*ESCRITOR REALIZA EL PAPEL DE CLIENTE*/
/*SOLICITA CONEXIÓN A SOCKET DETERMINADO*/
/*ESCRITOR ESCRIBE A SOCKET Y LEE DE STDIN*/
int main(int argc, char** argv)
{
    int connect_file_desc;
    int syscall_ret;
    char _buffer[256];

    if (argc != 2) usage();
    /*request connection to socket*/
    if ((connect_file_desc = clientConnection(argv[1])) < 0)
        error_exit("__clientConection__ error establishing conection", EXIT_FAILURE);
    else 
    {
        strcpy(_buffer, "connection to socket succesful\n");
        write(STDOUT, _buffer, strlen(_buffer));
    }

    /*read and write operations to socket here*/
    syscall_ret = read(STDIN, _buffer, sizeof(_buffer));
    if (syscall_ret == -1) 
        error_exit("__read__ error reading from std in", EXIT_FAILURE);

    syscall_ret = write(connect_file_desc, _buffer, syscall_ret);
    if (syscall_ret == -1) 
        error_exit("__write__ error writing to socket", EXIT_FAILURE);

   /*drop connection from socket*/
    closeConnection(connect_file_desc);
    return EXIT_SUCCESS;
}