#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

const char* str1 = "__SIGINT__ recibido!\n";

void func(int signum)
{
    if (signum == SIGINT)
    {
        write (1, str1, strlen(str1));
    }
}

int main(void)
{
    struct sigaction trat;
    sigset_t mask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);

    trat.sa_flags = 0;
    trat.sa_handler = &func;
    sigfillset(&trat.sa_mask);

    sigaction(SIGINT, &trat, NULL);

    int fd = open("input", O_RDONLY);
    if (fd == 1) perror("__open__ error");

    char c[1];

    while (read(fd, c, sizeof(char)) > 0)
    {
        write(1, c, sizeof(char));
        int f = lseek(fd, 4, SEEK_CUR);
        printf("file offset: %d\n", f);
    }
    close(fd);
}