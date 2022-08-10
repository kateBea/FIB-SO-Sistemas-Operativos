#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

#define STDOUT 1

void usage(void)
{
	char buffer[128];
	sprintf(buffer, "usage: ./myPS2 username\n");
	write(STDOUT, buffer, strlen(buffer));
	exit(EXIT_FAILURE);
}

void error_y_exit(const char* msg, int exit_status)
{
	perror(msg);
	exit(exit_status);
}

/* Ejecuta el comando ps –u username mediante la llamada al sistema execlp */
/* Devuelve: el código de error en el caso de que no se haya podido mutar */
void muta_a_PS(char* username)
{
	execlp("ps", "ps", "-u", username, (char*)NULL);
	error_y_exit("Ha fallado la mutación al ps", 1);
}

int main(int argc, char** argv)
{
	if (argc < 2) usage();
	char buffer[128];
	int pid;

	/*Número hijos a crear*/
	int num_hijos = argc - 1;

	for (int i = 1; i < num_hijos; ++i) {
		pid = fork();
		switch (pid)
		{
		case 0:
			sprintf(buffer, "HIJO: mi PID es: %d\n", getpid());
			write(STDOUT, buffer, strlen(buffer));
			sprintf(buffer, "HIJO: El paramtro de pasado es: %s\n", argv[i]);
			write(STDOUT, buffer, strlen(buffer));
			muta_a_PS(argv[i]);
			break;
		case -1:
			error_y_exit("Error al ejecutar el fork()", EXIT_FAILURE);
			break;
		}
	}
	sprintf(buffer, "PADRE: He acabado creacion de %d hijos. Mi PID es: %d\n", num_hijos, getpid());
	write(STDOUT, buffer, strlen(buffer));

	char c[1];
	int ret;
	int exit_val;
	while ((ret=waitpid(-1, &exit_val, 0)) > 0) {
		read(0, c, sizeof(char));

		int exit_code;
		if (WIFEXITED(exit_val)) {
			sprintf(buffer, "PADRE: Hijo con PID (%d) acaba con exit_code %d\n", ret, WEXITSTATUS(exit_val));
			write(STDOUT, buffer, strlen(buffer));
		}
	}

	read(0, c, sizeof(char));

	return EXIT_SUCCESS;
}