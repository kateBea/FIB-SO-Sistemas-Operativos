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

void usage(void)
{
    char buffer[128];
    sprintf(buffer, "usage: lector_socket [socket]\n");
    write(STDERR, buffer, strlen(buffer));
    sprintf(buffer, "this program creates socket to given address and accepts client connection requests\n");
    write(STDERR, buffer, strlen(buffer));
    sprintf(buffer, "[socket] may be the address of the socket itself\n");
    write(STDERR, buffer, strlen(buffer));
    exit(EXIT_FAILURE);
}

/*Output str to std error and exit program with code exit_code*/
void error_exit(const char* str, int exit_code)
{
    perror(str);
    exit(exit_code);
}

/*EL LECTOR REALIZA EL PAPEL DE SERVIDOR*/
/*CREA SOCKET Y ESPRA PETICIONES DE CONEXIÓN POR PARTE DE CLIENTE*/
/*LECTOR LEE DE SOCKET Y ESCRIBE A STDOUT*/
int main(int argc, char** argv)
{
    int socket_file_desc;
    int connect_file_desc;
    int syscall_ret;
    char _buffer[256];

    if (argc != 2) usage();

    /*socket creation*/
    if ((socket_file_desc = createSocket(argv[1])) < 0)
        error_exit("__createSocket__ error creating socket", EXIT_FAILURE);

    connect_file_desc = serverConnection(socket_file_desc);
    if (connect_file_desc < 0) 
        error_exit("__serverConnection__ error connecting to server", EXIT_FAILURE);

    /*read and write operations go here*/
    syscall_ret = read(connect_file_desc, _buffer, sizeof(_buffer));
    if (syscall_ret == -1) 
        error_exit("__read__ error reading from socket", EXIT_FAILURE);

    syscall_ret = write(STDOUT, _buffer, syscall_ret);
    if (syscall_ret == -1) 
        error_exit("__write__ error writing to std out", EXIT_FAILURE);

    /*clean up. Delete socket and close connection*/
    closeConnection(connect_file_desc);
    deleteSocket(socket_file_desc, argv[1]);
    return EXIT_SUCCESS;
}