#include "builtin.h"
#include "history.h"

#include <iostream>
#include <unistd.h>
#include <limits.h>

using namespace std;

bool isBuiltin(Command &command)
{
    if(command.args.empty())
        return false;

    string cmd = command.args[0];

    return (
        cmd=="cd" ||
        cmd=="pwd" ||
        cmd=="history" ||
        cmd=="help" ||
        cmd=="clear"
    );
}

void executeBuiltin(Command &command)
{
    string cmd = command.args[0];

    // cd
    if(cmd=="cd")
    {
        if(command.args.size()<2)
        {
            cerr<<"cd: missing operand"<<endl;
            return;
        }

        if(chdir(command.args[1].c_str())!=0)
        {
            perror("cd");
        }
    }

    // pwd
    else if(cmd=="pwd")
    {
        char cwd[PATH_MAX];

        if(getcwd(cwd,sizeof(cwd))!=nullptr)
        {
            cout<<cwd<<endl;
        }
    }

    // history
    else if(cmd=="history")
    {
        showHistory();
    }

    // clear
    else if(cmd=="clear")
    {
        cout<<"\033[2J\033[H";
    }

    // help
    else if(cmd=="help")
    {
        cout<<"========== NeoShell ==========\n";

        cout<<"Built-in Commands\n\n";

        cout<<"cd <dir>\n";
        cout<<"pwd\n";
        cout<<"history\n";
        cout<<"clear\n";
        cout<<"help\n";
        cout<<"exit\n";
    }
}