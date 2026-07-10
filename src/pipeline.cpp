#include "pipeline.h"

#include <iostream>
#include <vector>

#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

void executePipeline(Command &command)
{
    int numCommands = command.pipeline.size();

    int prevPipe[2] = {-1, -1};

    for (int i = 0; i < numCommands; i++)
    {
        int currentPipe[2] = {-1, -1};

        // Create pipe except for last command
        if (i < numCommands - 1)
        {
            if (pipe(currentPipe) == -1)
            {
                perror("pipe");
                return;
            }
        }

        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork");
            return;
        }

        // Child Process
        if (pid == 0)
        {
            // Read from previous pipe
            if (i > 0)
            {
                dup2(prevPipe[0], STDIN_FILENO);
            }

            // Write to next pipe
            if (i < numCommands - 1)
            {
                dup2(currentPipe[1], STDOUT_FILENO);
            }

            // Close unused pipe ends
            if (prevPipe[0] != -1)
            {
                close(prevPipe[0]);
                close(prevPipe[1]);
            }

            if (currentPipe[0] != -1)
            {
                close(currentPipe[0]);
                close(currentPipe[1]);
            }

            // Convert arguments
            vector<char*> argv;

            for (auto &arg : command.pipeline[i])
                argv.push_back(arg.data());

            argv.push_back(nullptr);

            execvp(argv[0], argv.data());

            perror("execvp");
            exit(EXIT_FAILURE);
        }

        // Parent closes previous pipe
        if (prevPipe[0] != -1)
        {
            close(prevPipe[0]);
            close(prevPipe[1]);
        }

        prevPipe[0] = currentPipe[0];
        prevPipe[1] = currentPipe[1];
    }

    // Wait for all children
    for (int i = 0; i < numCommands; i++)
    {
        wait(nullptr);
    }
}