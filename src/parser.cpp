#include "parser.h"

#include <sstream>

using namespace std;

Command parseCommand(const string& input)
{
    Command cmd;

    stringstream ss(input);

    string token;

    vector<string> currentPipe;

    while (ss >> token)
    {

        // Input Redirection
        if (token == "<")
        {
            cmd.inputRedirect = true;

            ss >> cmd.inputFile;
        }

        // Output Redirection
        else if (token == ">")
        {
            cmd.outputRedirect = true;

            ss >> cmd.outputFile;
        }

        // Append
        else if (token == ">>")
        {
            cmd.outputRedirect = true;

            cmd.append = true;

            ss >> cmd.outputFile;
        }

        // Background Process
        else if (token == "&")
        {
            cmd.background = true;
        }

        // Pipe
        else if (token == "|")
        {
            cmd.pipeline.push_back(currentPipe);

            currentPipe.clear();
        }

        else
        {
            currentPipe.push_back(token);
        }
    }

    if (!currentPipe.empty())
    cmd.pipeline.push_back(currentPipe);

    // If there are no pipes, copy the command into args
    if (cmd.pipeline.size() == 1)
    {
        cmd.args = cmd.pipeline[0];
        cmd.pipeline.clear();
    }

    return cmd;
}