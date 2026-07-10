#include "signals.h"

#include <iostream>
#include <csignal>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

// Handle Ctrl + C
void sigintHandler(int sig)
{
    cout << endl;
}

// Clean up zombie processes
void sigchldHandler(int sig)
{
    while (waitpid(-1, nullptr, WNOHANG) > 0);
}

void initializeSignals()
{
    signal(SIGINT, sigintHandler);
    signal(SIGCHLD, sigchldHandler);
}