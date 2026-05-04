#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h>
#include "LineParser.h"
#include <sys/wait.h>

int debug = 0; // 0 - no debug, 1 - debug mode on
void printDebug(int pid, cmdLine *pCmdLine)
{
    fprintf(stderr, "PID: %d\n", pid);
    fprintf(stderr, "Executing file name: %s\n", pCmdLine->arguments[0]);

    if (pCmdLine->blocking)
    {
        fprintf(stderr, "Foreground/Background: Foreground\n");
    }
    else
    {
        fprintf(stderr, "Foreground/Background: Background\n");
    }
}
void execute(cmdLine *pCmdLine)
{
    if (strcmp(pCmdLine->arguments[0], "cd") == 0)
    {
        if (chdir(pCmdLine->arguments[1]) == -1) // change curr direc
        {
            perror("cd failed");
        }
        if (debug)
        {
            printf("Changed directory to %s\n", pCmdLine->arguments[1]);
        }
        return;
    }

    int pid = fork();
    if (pid == -1)
    {
        perror("fork failed");
        return;
    }
    if (pid == 0)
    {
        // running the executa
        if (execvp(pCmdLine->arguments[0], pCmdLine->arguments))
        { // search for the excute in the system's PATH
            perror("execv error");
            freeCmdLines(pCmdLine);
            _exit(1);
        }
    }
    else
    { // parent process
        printDebug(pid, pCmdLine);
        if (pCmdLine->blocking)
        {
            waitpid(pid, NULL, 0);
        }
    }
}

int main(int argc, char **argv)
{
    while (1)
    {
        char path[PATH_MAX];
        char input[2048];
        if (getcwd(path, PATH_MAX) == NULL)
        {
            perror("getcwd error");
            return 1;
        }
        printf("%s> ", path);
        if (fgets(input, 2048, stdin) == NULL)
        {
            perror("fgets error");
            return 1;
        }
        if (strncmp(input, "quit", 4) == 0)
        {
            break;
        }
        if (strstr(input, "-d") != NULL)
        { // need to turn on debug mode
            debug = 1;
        }
        cmdLine *cmd = parseCmdLines(input);
        if (cmd == NULL)
        {
            continue;
        }
        execute(cmd); // execute the command
        freeCmdLines(cmd);
    }
    return 0;
}