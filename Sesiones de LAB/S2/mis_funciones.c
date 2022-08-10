#include "mis_funciones.h"

//calcula x a la y
int exponenciacion(int x, int y)
{
	if (y == 0) return 1;
	else
	{
		int n = exponenciacion(x, y / 2);
		return (y % 2) == 0 ? n * n : n * n * x;
	}
}

//La funci�n devuelve 1 si el string representa un n�mero y 
//tiene como mucho 8 cifras, y 0 en cualquier otro caso.
//se asume el que el string acaba en con el caracter '\0'
int esNumero(char* str)
{
	if ((str == nullptr) || (strlen(str) > MAX_SIZE)) return 0;
	else {
		//se asume en este bloque que el string
		//tiene menos de MAX_SIZE caracteres
		bool isNegative;
		bool esCorrecto = true;
		int i;

		if (str[0] == '-' && strlen(str) > 1) {
			//el string puede ser un n�mero negativo
			//si es un numero negativo deberia tener al menos dos elementos
			//no tendria sentido que tuviera solo el caracter '-'
			isNegative = true;
			i = 1;

			while (str[i] != '\0' && esCorrecto) {
				bool isDigit = str[i] >= '0' && str[i] <= '9';
				if (!isDigit) esCorrecto = false;
				else ++i;
			}
		}
		else {
			//el string puede ser un n�mero positivo
			isNegative = false;
			i = 0;

			while (str[i] != '\0' && esCorrecto) {
				bool isDigit = str[i] >= '0' && str[i] <= '9';
				if (!isDigit) esCorrecto = false;
				else ++i;
			}
		}
		return esCorrecto == true ? 1 : 0;
	}
}

//La funci�n devuelve 1 si el string representa un n�mero y 0 en cualquier otro caso.
//se asume el que el string acaba en con el caracter '\0'
int esNumeroAlt(char* str)
{
	if (str == nullptr) return 0;
	else {
		//se asume en este bloque que el string
		//tiene menos de MAX_SIZE caracteres
		bool isNegative;
		bool esCorrecto = true;
		int i;

		if (str[0] == '-' && strlen(str) > 1) {
			//el string puede ser un n�mero negativo
			//si es un numero negativo deberia tener al menos dos elementos
			//no tendria sentido que tuviera solo el caracter '-'
			isNegative = true;
			i = 1;

			while (str[i] != '\0' && esCorrecto) {
				bool isDigit = str[i] >= '0' && str[i] <= '9';
				if (!isDigit) esCorrecto = false;
				else ++i;
			}
		}
		else {
			//el string puede ser un n�mero positivo
			isNegative = false;
			i = 0;

			while (str[i] != '\0' && esCorrecto) {
				bool isDigit = str[i] >= '0' && str[i] <= '9';
				if (!isDigit) esCorrecto = false;
				else ++i;
			}
		}
		return esCorrecto == true ? 1 : 0;
	}
}

//convierte un car�cter a n�mero (1 cifra). La funci�n
//asume que el car�cter se corresponde con el car�cter de un n�mero.
unsigned int char2int(char c) { return c - '0'; }

//retorna el string convertido en n�mero
//se asume el puntero no es nullptr, si el estring
//no es n�mero se retorna -1
int mi_atoi(char* s)
{
	int LIMIT = strlen(s);
	bool esCorrecto = true;
	bool esNegativo = false;
	int index;
	int resultado = 0;
	int base;

	if (s[0] == '-' && LIMIT > 1) {
		//si el numero es negativo necesita al menos
		//2 caracteres (excluyendo '\0')
		esNegativo = true;
		index = 1;
		base = exponenciacion(10, LIMIT - 2);

	}
	else {
		//si el numero es positivo empezamos
		//conversi�n desde el principio
		esNegativo = false;
		index = 0;
		base = exponenciacion(10, LIMIT - 1);
	}

	while (index < LIMIT && esCorrecto) {
		//si algun caracter no es d�gito el string no es v�lido
		if (!(s[index] >= '0' && s[index] <= '9')) esCorrecto = false;
		else {
			resultado += char2int(s[index]) * base;
			base /= 10;
			++index;
		}
	}
	if (esNegativo) resultado *= -1;
	return esCorrecto == true ? resultado : -1;
}
