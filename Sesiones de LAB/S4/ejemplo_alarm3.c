#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#define STDOUT  1

void error_y_exit(char *msg, int exit_status)
{
  perror(msg);
  exit(exit_status);
}

int segundos = 0;

void funcion_alarma(int signal)
{
  char buff[256];
  segundos = segundos + 10;
  sprintf(buff, "ALARMA: %d segundos%d\n", getpid(), segundos);
  write(STDOUT, buff, strlen(buff));
  write(STDOUT, buff, strlen(buff));
}

int main(int argc, char *argv[])
{
  struct sigaction sa;
  sigset_t mask;
  pid_t ret;

  /* EVITAMOS QUE NOS LLEGUE EL SIGALRM FUERA DEL SIGSUSPEND */
  sigemptyset(&mask);
  sigaddset(&mask, SIGALRM);
  sigprocmask(SIG_BLOCK, &mask, NULL);


  alarm(10);

  if ((ret = fork()) < 0)   error_y_exit("fork", 1);

  sa.sa_handler = &funcion_alarma;
  sa.sa_flags = SA_RESTART;
  sigfillset(&sa.sa_mask);

  if (ret == 0)
  {  
    /* CAPTURAMOS EL SIGNAL SIGALRM */
    if (sigaction(SIGALRM, &sa, NULL)) error_y_exit("sigaction", 1);
  }
  else if (ret < 0) error_y_exit("eror: fork()...", 1);

  /*NOTA: Sólo hijo captura signa*/
  /*NOTA: Padre ejecuta tratamiento por defecto de ALRM*/
  while (segundos < 100)
  {
    alarm(10);
    if (ret == 0) execlp("sleep", "sleep", "15", (char*)NULL);
    sigfillset(&mask);
    sigdelset(&mask, SIGALRM);
    sigdelset(&mask, SIGINT);
    sigsuspend(&mask);
  }
  exit(1);
}
