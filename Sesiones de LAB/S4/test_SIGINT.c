/*All of the signal blocking functions use a data structure called a signal 
set to specify what signals are affected. Thus, every activity involves two stages: 
creating the signal set, and then passing it as an argument to a library function.

These facilities are declared in the header file signal.h.

Data Type: sigset_t
The sigset_t data type is used to represent a signal set. Internally, it may be 
implemented as either an integer or structure type.

For portability, use only the functions described in this section to initialize,
 change, and retrieve information from sigset_t objects—don’t try to manipulate them directly.

There are two ways to initialize a signal set. You can initially specify it 
to be empty with sigemptyset and then add specified signals individually. Or 
you can specify it to be full with sigfillset and then delete specified signals individually.

You must always initialize the signal set with one of these two functions before
using it in any other way. Don’t try to set all the signals explicitly because the 
sigset_t object might include some other information (like a version field) that needs
 to be initialized as well. (In addition, it’s not wise to put into your program an assumption 
 that the system has no signals aside from the ones you know about.)

Function: int sigemptyset (sigset_t *set)
Preliminary: | MT-Safe | AS-Safe | AC-Safe | See POSIX Safety Concepts.

This function initializes the signal set set to exclude all of the defined 
signals. It always returns 0.

Function: int sigfillset (sigset_t *set)
Preliminary: | MT-Safe | AS-Safe | AC-Safe | See POSIX Safety Concepts.

This function initializes the signal set set to include all of the defined signals. 
Again, the return value is 0.

Function: int sigaddset (sigset_t *set, int signum)
Preliminary: | MT-Safe | AS-Safe | AC-Safe | See POSIX Safety Concepts.

This function adds the signal signum to the signal set set. All sigaddset does 
is modify set; it does not block or unblock any signals.

The return value is 0 on success and -1 on failure. The following errno 
error condition is defined for this function: EINVAL

The signum argument doesn’t specify a valid signal.

Function: int sigdelset (sigset_t *set, int signum)
Preliminary: | MT-Safe | AS-Safe | AC-Safe | See POSIX Safety Concepts.

This function removes the signal signum from the signal set set. All sigdelset does 
is modify set; it does not block or unblock any signals. The return value and error 
conditions are the same as for sigaddset.

Finally, there is a function to test what signals are in a signal set:

Function: int sigismember (const sigset_t *set, int signum)
Preliminary: | MT-Safe | AS-Safe | AC-Safe | See POSIX Safety Concepts.

The sigismember function tests whether the signal signum is a member of the signal set set. 
It returns 1 if the signal is in the set, 0 if not, and -1 if there is an error.

The following errno error condition is defined for this function: EINVAL

The signum argument doesn’t specify a valid signal.
*/


#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define true 1
#define MAX_CHAR 128
#define STDOUT 1

//escribe mensaje por pantalla
//indicando que ha recibido SIGINT
void cap_func(int s)
{
    char* buffer = malloc(sizeof(char)*MAX_CHAR);
    sprintf(buffer, "I received SIGINT signal. My PID is: %d\n", getpid());
    write(STDOUT, buffer, strlen(buffer));
    free(buffer);
}

//escribe mensaje por pantalla
//indicando que ha recibido SIGUSR1
void cap_func2(int s)
{
    char* buffer = malloc(sizeof(char)*MAX_CHAR);
    sprintf(buffer, "I received SIGUSR1 signal. My PID is: %d\n", getpid());
    write(STDOUT, buffer, strlen(buffer));
    free(buffer);
}

//escribe mensaje por pantalla
//indicando que ha recibido SIGUSR1
void cap_func3(int s)
{
    char* buffer = malloc(sizeof(char)*MAX_CHAR);
    sprintf(buffer, "I received SIGUSR2 signal. My PID is: %d\n", getpid());
    write(STDOUT, buffer, strlen(buffer));
    free(buffer);
}

void printError(void)
{
    char* buffer = malloc(sizeof(char)*MAX_CHAR);
    sprintf(buffer, "Error fork() syscall\n");
    write(STDOUT, buffer, strlen(buffer));
    free(buffer);
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
    int pid = fork();
    struct sigaction trat3;
    sigset_t* mask4;
    char* buffer = malloc(sizeof(char)*MAX_CHAR);

    switch (pid)
    {
    case 0:
        sprintf(buffer, "CHILD: %d\n", getpid());
        write(STDOUT, buffer, strlen(buffer));
        free(buffer);

        sigemptyset(mask4);
        trat3.sa_flags=0;
        trat3.sa_handler=cap_func3;

        sigaction(SIGUSR2, &trat3, NULL);

        while(1);
        break;
    case -1:
        printError();
        break;
    }

    sprintf(buffer, "PARENT: %d\n", getpid());
    write(STDOUT, buffer, strlen(buffer));
    free(buffer);

    struct sigaction trat;

    //creamos máscara de señales
    sigset_t mask;

    //vaciamos máscara de señales
    sigemptyset(&mask);

    //sa_flags  specifies  a set of flags which modify the behavior of the signal
    //0 => default behaviour (term, core, etc), SA_RESETHAND to restore default behaviour
    //after catching signal for first time
    trat.sa_flags=0;

    trat.sa_mask=mask;

    //acción al recibir SIGINT
    trat.sa_handler = cap_func;

    struct sigaction trat2;
    sigset_t mask3; 
    sigemptyset(&mask3);
    trat2.sa_flags=0;
    trat2.sa_handler=cap_func2;

    //Capturamos el signal
    sigaction(SIGINT, &trat, NULL);
    sigaction(SIGUSR1, &trat2, NULL);

    sigset_t mask1; sigfillset(&mask1);
    sigdelset(&mask1, SIGINT);
    sigdelset(&mask1, SIGUSR1);
    sigsuspend(&mask1);

    while(true);


    return EXIT_SUCCESS;
}