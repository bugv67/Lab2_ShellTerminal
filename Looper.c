#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <signal.h>
#include <string.h>

void handler(int sig)
{
    printf("\nRecieved Signal : %s\n", strsignal(sig));
    fflush(stdout);

    if (sig == SIGTSTP) // will frezze the process
    {
        signal(SIGCONT, handler);
    }
    else if (sig == SIGCONT) // will wake up
    {
        signal(SIGTSTP, handler);
    }
    signal(sig, SIG_DFL); // restore default handler for the signal
    raise(sig);           // re send the signal to actally do it
}

int main(int argc, char **argv)
{
    printf("Starting the program\n");
    // the signals the progran should handle!
    signal(SIGINT, handler);
    signal(SIGTSTP, handler);
    signal(SIGCONT, handler);

    while (1)
    {
        sleep(1);
    }

    return 0;
}