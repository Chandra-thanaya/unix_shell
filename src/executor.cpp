#include "executor.h"
#include "redirect.h"
#include "pipeline.h"

#include <iostream>
#include <vector>

#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

void executeCommand(Command &command)
{
    // Nothing to execute
    if (command.args.empty() && command.pipeline.empty())
        return;

    // Pipeline command
    if (!command.pipeline.empty())
    {
        executePipeline(command);
        return;
    }

    // Create child process
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    // -------------------------
    // Child Process
    // -------------------------
    if (pid == 0)
    {
        // Handle input/output redirection
        if (!setupRedirection(command))
            exit(EXIT_FAILURE);

        // Convert vector<string> to char*[]
        vector<char*> argv;
        argv.reserve(command.args.size() + 1);

        for (auto &arg : command.args)
            argv.push_back(arg.data());

        argv.push_back(nullptr);

        // Execute command
        execvp(argv[0], argv.data());

        // Only reached if execvp() fails
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    // -------------------------
    // Parent Process
    // -------------------------
    if (!command.background)
    {
        waitpid(pid, nullptr, 0);
    }
    else
    {
        cout << "[Background PID: " << pid << "]" << endl;
    }
}