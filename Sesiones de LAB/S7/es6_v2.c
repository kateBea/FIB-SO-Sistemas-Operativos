#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

const char* str1 = "__read__ correcto\n";
const char* str2 = "__read__ con error (diferente de interrupción por signal)\n";
const char* str3 = "__read__ interrumpido por signal\n";

void func(int signum)
{
  if (signum == SIGINT)
  {
    char buffer[128];
    sprintf(buffer, "SIGINT recibido!\n");
    write(2, buffer, strlen(buffer));
  }
}

int main(void)
{
  struct sigaction trat;
  sigset_t mask;
  char c;
  int ret;

  sigemptyset(&mask);
  sigaddset(&mask, SIGINT);

  trat.sa_flags = SA_RESTART;  
  trat.sa_handler = &func;
  sigfillset(&trat.sa_mask);

  if (sigaction(SIGINT, &trat, NULL) == -1) 
    perror("error __sigaction__");

  ret = read (0, &c, sizeof (char));
  if (ret == -1)
  {
    //ERROR //READ INTERRUMPIDO POR SIGNAL
    //The call was interrupted by a signal before any data was read
    if (errno == EINTR) write(1, str3, strlen(str3));
    //Other interrupcions causes
    else write(1, str2, strlen(str2));
  }
  else {
    //READ CORRECTO
    write(1, str1, strlen(str1));
    write (1, &c, sizeof (char));
  }

}
