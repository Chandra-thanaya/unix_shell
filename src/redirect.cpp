#include "redirect.h"

#include <iostream>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

static int stdinBackup = -1;
static int stdoutBackup = -1;

bool setupRedirection(Command &command)
{
    // Backup stdin/stdout
    stdinBackup = dup(STDIN_FILENO);
    stdoutBackup = dup(STDOUT_FILENO);

    // Input Redirection
    if(command.inputRedirect)
    {
        int fd = open(command.inputFile.c_str(), O_RDONLY);

        if(fd < 0)
        {
            perror("open");
            return false;
        }

        dup2(fd, STDIN_FILENO);
        close(fd);
    }

    // Output Redirection
    if(command.outputRedirect)
    {
        int flags = O_WRONLY | O_CREAT;

        if(command.append)
            flags |= O_APPEND;
        else
            flags |= O_TRUNC;

        int fd = open(
            command.outputFile.c_str(),
            flags,
            0644
        );

        if(fd < 0)
        {
            perror("open");
            return false;
        }

        dup2(fd, STDOUT_FILENO);
        close(fd);
    }

    return true;
}

void restoreRedirection()
{
    if(stdinBackup != -1)
    {
        dup2(stdinBackup, STDIN_FILENO);
        close(stdinBackup);
        stdinBackup = -1;
    }

    if(stdoutBackup != -1)
    {
        dup2(stdoutBackup, STDOUT_FILENO);
        close(stdoutBackup);
        stdoutBackup = -1;
    }
}