#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
/* ESTE PROCESO PROGRAMA UN TEMPORIZADOR PARA  DENTRO DE 15 SEGUNDOS Y SE BLOQUEA A ESPERAR QUE LLEGUE */
/* LA ACCION POR DEFECTO DEL SIGALRM ES ACABAR EL PROCESO */

void ala(int s)
{
    printf("I received sigalarm\n");
}

int main(int argc, char *argv[])
{
  
  /*
  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGALRM);
  sigprocmask(SIG_BLOCK, &mask, NULL);
  */

  alarm(15);
  struct sigaction trat;
  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGALRM);
  trat.sa_handler=ala;
  trat.sa_flags=SA_RESETHAND;

  sigaction(SIGALRM, &trat, NULL);
  while(1);
  /*
  sigfillset(&mask);
  sigdelset(&mask, SIGALRM);
  sigdelset(&mask, SIGINT);
  sigsuspend(&mask);
  exit(1);
  */
}
