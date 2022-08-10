#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char buff[100];

void suma(int op1, int op2, int *res)
{
    *res = op1 + op2;
}

int j;

int main(int argc, char *argv[])
{
    int i; i = atoi(argv[1]);
    int* s; j = atoi(argv[2]);
    s = malloc(sizeof(int));

    s[3] = 1;
    suma(i, j, s);
    sprintf(buff,"suma de %d y %d es %d\n", i, j, *s);
    write(1, buff, strlen(buff));

    return EXIT_SUCCESS;
}