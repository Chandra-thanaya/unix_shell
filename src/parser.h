#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

struct Command {

    // Main command arguments
    std::vector<std::string> args;

    // Input redirection
    bool inputRedirect = false;
    std::string inputFile;

    // Output redirection
    bool outputRedirect = false;
    std::string outputFile;

    // >>
    bool append = false;

    // &
    bool background = false;

    // Commands separated by |
    std::vector<std::vector<std::string>> pipeline;
};

Command parseCommand(const std::string& input);

#endif