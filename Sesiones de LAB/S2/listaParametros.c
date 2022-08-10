#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STDOUT 1

void usage(void)
{
	char buffer[128];
	sprintf(buffer, "Usage:listaParametros arg1 [arg2..argn]\n");
	write(STDOUT, buffer, strlen(buffer));
	sprintf(buffer, "Este programa escribe por su salida la lista de argumentos que recibe\n");
	write(STDOUT, buffer, strlen(buffer));
	exit(EXIT_FAILURE);
}

void main(int argc,char *argv[])
{
	char buf[80];
	int i;
	if (argc < 2) usage();
	for (i = 0; i < argc; i++) {
		if (i == 0) {
			sprintf(buf, "El argumento %d es %s (es el nombre del ejecutable)\n", i, argv[i]);
		}
		else {
			sprintf(buf, "El argumento %d es %s\n", i, argv[i]);
		}
		write(1, buf, strlen(buf));
	}
	return;
}
