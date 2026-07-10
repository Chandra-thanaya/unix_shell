#include <iostream>
#include <string>
#include <unistd.h>
#include <limits.h>

#include "parser.h"
#include "executor.h"
#include "builtin.h"
#include "history.h"
#include "signals.h"
#include "custom.h"

using namespace std;

int main() {

    // Initialize signal handlers
    initializeSignals();

    string input;

    while (true) {

        // Current Working Directory
        char cwd[PATH_MAX];
        getcwd(cwd, sizeof(cwd));

        // Prompt
        cout << "NeoShell:" << cwd << " $ ";

        // Read command
        if (!getline(cin, input)) {
            cout << endl;
            break;
        }

        // Ignore empty commands
        if (input.empty())
            continue;

        // Save command in history
        addHistory(input);

        // Parse command
        Command command = parseCommand(input);

        // Exit shell
        if (command.args.size() > 0 &&
            command.args[0] == "exit")
            break;

        // Execute Built-in Commands
        if (isBuiltin(command)){
            executeBuiltin(command);
        }
        else if (isCustomCommand(command))
        {
            executeCustomCommand(command);
        }
        else
        {
            executeCommand(command);
        }

    }

    cout << "Exiting NeoShell..." << endl;

    return 0;
}
