#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define REGION_SIZE 4096
#define MAX_BUFFER  128
#define STDOUT      1

int *p;

void routine(int signum)
{
  char* buffer = malloc(sizeof(char)*MAX_BUFFER);
  sprintf(buffer, "Referencia de memoria invalida\n");
  write(STDOUT, buffer, strlen(buffer));
  exit(EXIT_FAILURE);
  free(buffer);
}

int main(int argc, char *argv[])
{
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

  *p = 5;

  sprintf(buff, "\tp Address: %p, p value: %p, *p: %d\n", &p, p, *p);
  write(1, buff, strlen(buff));

  exit(0);
}
