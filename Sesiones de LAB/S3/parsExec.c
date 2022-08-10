#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

#define MAX_HIJOS 4
#define MAX_BUFFER 128
#define STDOUT 1
#define true 1
#define false 0

//Escribe mensaje indicando como usar el programa
void usage(void)
{
	char buffer[MAX_BUFFER];
	sprintf (buffer, "usage: ./parsExec arg1...argN\n"); 
	write(STDOUT, buffer, strlen(buffer));
	exit(EXIT_FAILURE);
}

//Termina el princeso indicando error de terminacion
void error_y_exit(const char* msg, int exit_status)
{
	perror(msg);
	exit(exit_status);
}

void main(int argc, char** argv)
{
	if (argc < 2) usage();
	int pid;
	char buffer[MAX_BUFFER];

	for (int i = 0; i < MAX_HIJOS; ++i) {
		pid = fork();
		switch (pid) {
		case 0:
			//CÓDIGO A EJECUTAR EN EL CASO
			//DE NO HABER ERROR AL MUTAR
			switch (i) {
				//LOS ARGUMENTOS DE MUTACIÓN SON ÚNICOS POR CADA HIJO
			case 0:
				execlp("./listaParametros", "listaParametros", "a", "b", (char*)NULL);
				error_y_exit("Error al ejecutar execlp()", EXIT_FAILURE);
				break;
			case 1:
				execlp("./listaParametros", "listaParametros", (char*)NULL);
				error_y_exit("Error al ejecutar execlp()", EXIT_FAILURE);
				break;
			case 2:
				execlp("./listaParametros", "listaParametros", "25", "4", (char*)NULL);
				error_y_exit("Error al ejecutar execlp()", EXIT_FAILURE);
				break;
			default:
				execlp("./listaParametros", "listaParametros", "1024", "hola", "adios", (char*)NULL);
				error_y_exit("Error al ejecutar execlp()", EXIT_FAILURE);
				break;
			}
			break;
		case -1:
			error_y_exit("Error al ejecutar fork()", EXIT_FAILURE);
			break;
		}

		/*Si no añadimos el condicional abajo no se garantiza que se ejecuten en el
		orden del ejemplo, dependerá de como el SO organiza el uso de CPU */

		#if false
		//Poner a true la directiva para
		//secuenciar la creación y ejecución de hijos
		if (i < 3) {
			waitpid(-1, NULL, 0);
			sprintf(buffer, "\n"); write(STDOUT, buffer, strlen(buffer));
		}
		#endif
	}

	/*Este bucle es inecesario si se ejecuta el waitpid() del bucle for()*/
	while (waitpid(-1, NULL, 0) > 0);
	
}