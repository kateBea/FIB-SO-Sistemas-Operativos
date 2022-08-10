#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

//definiciones
#define STDOUT 1
#define MAX_SIZE 8
#define nullptr NULL
#define bool int
#define true 1
#define false 0

//Función que retorna el resultado de elevar x a y
int exponenciacion(int x, int y);

//La función devuelve 1 si el string representa un número y 
//tiene como mucho 8 cifras, y 0 en cualquier otro caso.
//se asume el que el string acaba en con el caracter '\0'
int esNumero(char* str);

//La función devuelve 1 si el string representa un número y
//0 en cualquier otro caso. Se asume el que el string acaba 
//en con el caracter '\0'
int esNumeroAlt(char* str);

//Retorna el string convertido en número. Se asume el 
//puntero no es nullptr, si el string no es número se retorna -1
int mi_atoi(char* s);