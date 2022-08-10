#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define STDOUT 1

void usage(void)
{
	char buffer[128];
	sprintf(buffer, "usage: ./myPS username\n");
	write(STDOUT, buffer, strlen(buffer));
	exit(EXIT_FAILURE);
}

void error_y_exit(const char* msg, int exit_status)
{
	perror(msg);
	exit(exit_status);
	exit(exit_status);
}

int main(int argc, char** argv)
{
	if (argc < 2) usage();
	char buffer[128];

	int pid = fork();
	switch (pid)
	{
	case 0:
		sprintf(buffer, "HIJO: mi PID es: %d\n", getpid());
		write(STDOUT, buffer, strlen(buffer));
		sprintf(buffer, "HIJO: El paramtro de pasado es: %s", argv[1]);
		write(STDOUT, buffer, strlen(buffer));
		while (1);
		break;
	case -1:
		error_y_exit("Error al ejecutar el fork()", EXIT_FAILURE);
		break;
	default:
		sprintf(buffer, "PADRE: mi PID es: %d\n", getpid());
		write(STDOUT, buffer, strlen(buffer));
		while (1);
		break;
	}

	return EXIT_SUCCESS;
}