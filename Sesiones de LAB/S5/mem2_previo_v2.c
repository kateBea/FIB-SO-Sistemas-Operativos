/*SOME NOTES for sbrk(): */
/*
brk() and sbrk() change the location of the program break, 
which defines the end of the process's data segment
(i.e., the program break is the first location after the 
end of the uninitialized data  segment).   Increasing
the program break has the effect of allocating memory to 
the process; decreasing the break deallocates memory.

brk() set break to the address you pass as parameter and 
return 0, -1 on error

sbrk() increment program's data space (starting from break)
X bytes according to the parameter.  return pointer to previous break address

call to sbrk() with param. 0 returns pointer to previous 
break address and doesnt inscrement data segment space

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define STDIN     0
#define STDOUT    1
#define STDERR    2
#define MAX_SIZE  40960


/* readint - Devuelve un entero leido desde teclado */
int readint(void)
{
  char buff[100];
  int x;
  x = read(STDIN, &buff, sizeof(buff));
  if (x < 0)
  {
    perror(" ERROR leyendo numero ");
    exit(EXIT_SUCCESS);
  }
  buff[x - 1] = '\0'; /* sustituir '\n' por '\0' */
  x = atoi(buff);
  return x;
}

/*Inicializa vector con num_elems elementos*/
void fillvector(int *vector, int num_elems)
{
  for (int i = 0; i < num_elems; i++) vector[i] = i;
}

int *vector;

int main(int argc, char *argv[])
{
  int i;
  int n;
  int s = 0;
  char buff[100];

  if (argc != 1)
  {
    sprintf(buff, "Usage: %s \n", argv[0]);
    write(STDERR, buff, strlen(buff));
    exit(EXIT_FAILURE);
  }
  sprintf(buff, "Soy el proceso %d\n", getpid());
  write(STDOUT, buff, strlen(buff));

  sprintf(buff, "Introduce el numero de elementos del vector y pulsa Return:");
  write(STDOUT, buff, strlen(buff));
  n = readint();

  /*increase program*/
  vector = sbrk(sizeof(int)*MAX_SIZE);
  fillvector(vector, n);

  for (i = 0; i < n; i++) s += vector[i];
  sprintf(buff, "la suma de los %d elementos del vector es %d\n", n, s);
  write(1, buff, strlen(buff));

  sprintf(buff, "Pulsa Return para acabar la ejecución\n");
  write(1, buff, strlen(buff));
  read(STDIN, buff, 1);

  exit(EXIT_SUCCESS);
}
