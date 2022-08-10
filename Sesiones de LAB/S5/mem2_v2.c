#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define REGION_SIZE 4096
#define MAX_BUFFER  128
#define STDOUT      1
#define STDERR      2
#define MAX_SIZE    4096

int *p;

void routine(int signum)
{
  char* buffer = malloc(sizeof(char)*MAX_BUFFER);
  sprintf(buffer, "Direccion variable p: %p\n", &p);
  write(STDOUT, buffer, strlen(buffer));
  sprintf(buffer, "Valor variable p: %p\n", p);
  write(STDOUT, buffer, strlen(buffer));
  sprintf(buffer, "Dirección donde finaliza heap: %p\n", p+1);
  write(STDOUT, buffer, strlen(buffer));
  exit(EXIT_FAILURE);
  free(buffer);
}

int main(int argc, char *argv[])
{
  int i = 0;
  char buff[256];

  sprintf(buff, "Addresses:\n");
  write(1, buff, strlen(buff));
  sprintf(buff, "\tp: %p\n", &p);
  write(1, buff, strlen(buff));

  struct sigaction trat;
  sigset_t mask;
  sigemptyset(&mask); 
  sigaddset(&mask, SIGSEGV);

  trat.sa_flags = 0;
  trat.sa_mask = mask;
  trat.sa_handler = &routine;

  sigaction(SIGSEGV, &trat, NULL);

  p = sbrk(sizeof(int)*MAX_SIZE);

  if (p == NULL)
  {
    sprintf(buff, "ERROR en el malloc\n");
    write(STDERR, buff, strlen(buff));
  }
  int* start_point = p;
  while (p < (start_point+MAX_SIZE))
  {
    *p = i;
    sprintf(buff, "\tProgram code -- p address: %p, p value: %p, *p: %d\n",
            &p, p, *p);
    write(1, buff, strlen(buff));
    p++;
    i++;
  }
}
