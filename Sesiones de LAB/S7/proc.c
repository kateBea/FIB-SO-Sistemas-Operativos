#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int num=0x2943;
    char buff[12];
    sprintf(buff, "%d", num);
    write(1,&buff,sizeof(int)); // Si el canal 1 es la consola, veremos basura, ya que solo acepta ascii.

    return EXIT_SUCCESS;
}