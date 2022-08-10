#include <mis_funciones.h>

void usage(void)
{
	char buffer[128];
	sprintf(buffer, "Usage: ./suma arg1 arg2 [arg3..argn]\n");
	write(STDOUT, buffer, strlen(buffer));
	sprintf(buffer, "Este program escribe por consola la suma de los numeros del argv\n");
	write(STDOUT, buffer, strlen(buffer));
	exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
	char buffer[128];
	if (argc < 3) usage();
	else {
		int suma = 0;
		bool paramCorrectos = true;
		int ret;
		for (int i = 1; i < argc && paramCorrectos; ++i) {
			if (esNumeroAlt(argv[i])) suma += mi_atoi(argv[i]);
			else {
				paramCorrectos = false;
				ret = i;
			}
		}

		if (paramCorrectos) sprintf(buffer, "La suma es: %d\n", suma);
		else sprintf(buffer, "Error: el parametro '%s' no es un numero\n", argv[ret]);
		write(STDOUT, buffer, strlen(buffer));
	}
	return EXIT_SUCCESS;
}
