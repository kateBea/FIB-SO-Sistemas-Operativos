#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

//defines
#define STDOUT 1
#define MAX_SIZE 8
#define nullptr NULL
#define bool int
#define true 1
#define false 0
  
//calcula x a la y
  int
  exponenciacion (int x, int y) 
 { 
if (y == 0)
    return 1;
  
  else
    {
      
int n = exponenciacion (x, y / 2);
      
return (y % 2) == 0 ? n * n : n * n * x;
    
}

}


 
//La función devuelve 1 si el string representa un número y 
//tiene como mucho 8 cifras, y 0 en cualquier otro caso.
//se asume el que el string acaba en con el caracter '\0'
  int
  esNumero (char *str) 
 { 
if ((str == nullptr) || (strlen (str) > MAX_SIZE))
    return 0;
  
  else
    {
      
	//se asume en este bloque que el string
	//tiene menos de MAX_SIZE caracteres
      bool isNegative;
      
bool esCorrecto = true;
      
 
int i;
      
 
if (str[0] == '-' && strlen (str) > 1)
	{
	  
	    //el string puede ser un número negativo
	    //si es un numero negativo deberia tener al menos dos elementos
	    //no tendria sentido que tuviera solo el caracter '-'
	    //strlen() devuelve el tamaño del string sin contar '\0'
	    //(por tanto en realidad esperamos que para negativos el array tengo tres elementos
	    //como minimo e.g.: {'-', '1', '\0'} si fuese -1
	    isNegative = true;
	  
i = 1;
	  
while (str[i] != '\0' && esCorrecto)
	    
	    {
	      
bool isDigit = str[i] >= '0' && str[i] <= '9';
	      
if (!isDigit)
		esCorrecto = false;
	      
	      else
		++i;
	    
}
	
}
      
      else
	{
	  
	    //el string puede ser un número positivo
	    isNegative = false;
	  
i = 0;
	  
while (str[i] != '\0' && esCorrecto)
	    
	    {
	      
bool isDigit = str[i] >= '0' && str[i] <= '9';
	      
if (!isDigit)
		esCorrecto = false;
	      
	      else
		++i;
	    
}
	
}
      
return esCorrecto == true ? 1 : 0;
    
}

}


 
int
main (int argc, char **argv) 
 { 
char buffer[128];
  
if (argc < 2)
    {
      
sprintf (buffer,
		"Se necesitan mas argumentos. Ejemplo: ./numeros 123...\n");
    
}
  
  else
    {
      
for (int i = 1; i < argc; ++i)
	{
	  
if (esNumero (argv[i]))
	    sprintf (buffer, "El argumento '%s' es numero\n", argv[i]);
	  
	  else
	    sprintf (buffer, "El argumento '%s' no es numero\n", argv[i]);
	  
write (STDOUT, buffer, strlen (buffer));
	
}
    
}
  
 
return EXIT_SUCCESS;

}
