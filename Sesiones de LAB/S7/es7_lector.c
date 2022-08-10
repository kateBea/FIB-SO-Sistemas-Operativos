#include <unistd.h>
#include <stdio.h>

int
main ()
{
  int buffer;
  char out[5];

  read(0, &buffer, sizeof(int));
  sprintf(out, "%d",buffer);
  write (1, &out, sizeof (int));
  
}
