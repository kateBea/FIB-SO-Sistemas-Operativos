#include <mis_funciones.h>

void usage2(void)
{
	char buffer[128];

	sprintf(buffer, "usage: ./words string1 string2...stringN\n");
	write(STDOUT, buffer, strlen(buffer));
	sprintf(buffer, "Este programa cuenta el numero de palabras que hay en el string pasado como primer parametro.\n");
	write(STDOUT, buffer, strlen(buffer));
	exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
	if (argc < 2) usage2();

	int totalPalabras = 0;
	char* it = argv[1];
	while(*it != '\0') {
		/*Consideraremos que empieza una nueva palabra después 
		de: un espacio, un punto, una coma y un salto de línea (\n).*/
		bool letra = (*it >= 'a' && *it <= 'z') || (*it >= 'A' && *it <= 'Z');
		bool numero = *it >= '0' && *it <= '9';
		bool esPalabra = letra || numero;
		while (esPalabra && *it != '\0') {
			if (( * it == ' ') || (*it == '.') || (*it == ',') || (*it == '\n')) {
				esPalabra = false;
				totalPalabras++;
			}
			else ++it;
		}

		//condicional en caso de tener una palbra justo antes
		//final de la cadena de caracteres
		if (esPalabra && *it == '\0') ++totalPalabras;
		if (*it != '\0') ++it;
	}
	char buffer[128];
	sprintf(buffer, "%d palabra(s)\n", totalPalabras);
	write(STDOUT, buffer, strlen(buffer));
	return EXIT_SUCCESS;
}