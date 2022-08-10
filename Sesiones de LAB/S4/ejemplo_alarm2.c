#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

#define STDOUT 1

void error_y_exit(char *msg, int exit_status)
{
  perror(msg);
  exit(exit_status);
}

/* ESTA VARIABLE SE ACCEDE DESDE LA FUNCION DE ATENCION AL SIGNAL Y DESDE EL MAIN */
int segundos = 0;
/* FUNCION DE ATENCION AL SIGNAL SIGALRM */
void funcion_alarma(int sig_num)
{
  char buff[256];
  if (sig_num == SIGALRM) 
  {
    /*Tratamiento asociado SIGALRM*/
    segundos = segundos + 10;
  }
  if (sig_num == SIGUSR1)
  {
    /*Tratamiento asociado SIGUSR1*/
    sprintf(buff, "SIGUSR1(pid %d). Alrm->%d(s)\n", getpid(), segundos);
    write(STDOUT, buff, strlen(buff));
  }
}

int main(int argc, char *argv[])
{
  struct sigaction sa;
  sigset_t mask;

  sigemptyset(&mask);
  sigaddset(&mask, SIGALRM);
  sigaddset(&mask, SIGUSR1);
  sigprocmask(SIG_BLOCK, &mask, NULL);

  /* REPROGRAMAMOS EL SIGNAL SIGALRM */
  sa.sa_handler = &funcion_alarma;
  sa.sa_flags = SA_RESTART;
  sigfillset(&sa.sa_mask);

  if (sigaction(SIGALRM, &sa, NULL) < 0)
    error_y_exit("error sigaction_SIGALRM", 1);
  if (sigaction(SIGUSR1, &sa, NULL) < 0)
    error_y_exit("error sigaction_SIGUSR1", 1);

  while (segundos < 100)
  {
     /* Programamos la alarma para dentro de 10 segundos */
    alarm(10);
    
    /* Nos bloqueamos a esperar que nos llegue un evento */
    sigfillset(&mask);
    sigdelset(&mask, SIGALRM);
    sigdelset(&mask, SIGINT);
    sigdelset(&mask, SIGUSR1);
    sigsuspend(&mask);
  }
  exit(1);
}
