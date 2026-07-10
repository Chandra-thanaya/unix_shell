#include "custom.h"

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

bool isCustomCommand(Command &command)
{
    if (command.args.empty())
        return false;

    string cmd = command.args[0];

    return (
        cmd == "say" ||
        cmd == "display" ||
        cmd == "calendar" ||
        cmd == "open"
    );
}

void executeCustomCommand(Command &command)
{
    string cmd = command.args[0];

    // say
    if (cmd == "say")
    {
        for (size_t i = 1; i < command.args.size(); i++)
            cout << command.args[i] << " ";

        cout << endl;
    }

    // display
    else if (cmd == "display")
    {
        if (command.args.size() < 2)
        {
            cerr << "display: missing filename\n";
            return;
        }

        ifstream file(command.args[1]);

        if (!file)
        {
            cerr << "Cannot open file.\n";
            return;
        }

        string line;

        while (getline(file, line))
            cout << line << endl;

        file.close();
    }

    // calendar
    else if (cmd == "calendar")
    {
        if (command.args.size() == 3)
        {
            string commandLine =
                "cal " +
                command.args[1] +
                " " +
                command.args[2];

            system(commandLine.c_str());
        }
        else
        {
            cerr << "Usage: calendar <month> <year>\n";
        }
    }

    // open
    else if (cmd == "open")
    {
        if (command.args.size() < 2)
        {
            cerr << "open: missing filename\n";
            return;
        }

#ifdef __linux__
        string commandLine = "xdg-open \"" + command.args[1] + "\"";
#elif _WIN32
        string commandLine = "start " + command.args[1];
#else
        string commandLine = "open " + command.args[1];
#endif

        system(commandLine.c_str());
    }
}