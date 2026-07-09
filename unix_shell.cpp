// unix_shell.cpp

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

using namespace std;

vector<string> historyList;

// Ctrl+C Handler
void signalHandler(int sig) {
    cout << "\nmyshell> ";
    cout.flush();
}

// Split string by delimiter
vector<string> split(string str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter)) {
        if (!token.empty())
            tokens.push_back(token);
    }

    return tokens;
}

// Convert vector<string> to char**
char** convert(vector<string>& args) {
    char** argv = new char*[args.size() + 1];

    for (int i = 0; i < args.size(); i++)
        argv[i] = &args[i][0];

    argv[args.size()] = nullptr;
    return argv;
}

void execute(vector<string> args) {

    int in = -1, out = -1;
    bool append = false;

    vector<string> cmd;

    for (int i = 0; i < args.size(); i++) {

        if (args[i] == "<") {
            in = open(args[++i].c_str(), O_RDONLY);
        }

        else if (args[i] == ">") {
            out = open(args[++i].c_str(),
                       O_CREAT | O_WRONLY | O_TRUNC,
                       0644);
        }

        else if (args[i] == ">>") {
            append = true;
            out = open(args[++i].c_str(),
                       O_CREAT | O_WRONLY | O_APPEND,
                       0644);
        }

        else
            cmd.push_back(args[i]);
    }

    pid_t pid = fork();

    if (pid == 0) {

        if (in != -1) {
            dup2(in, STDIN_FILENO);
            close(in);
        }

        if (out != -1) {
            dup2(out, STDOUT_FILENO);
            close(out);
        }

        char** argv = convert(cmd);

        execvp(argv[0], argv);

        perror("Command failed");
        exit(1);
    }

    else {
        waitpid(pid, nullptr, 0);
    }
}

// Execute Pipe
void executePipe(string input) {

    vector<string> cmds = split(input, '|');

    int fd[2];
    int in = 0;

    for (int i = 0; i < cmds.size(); i++) {

        pipe(fd);

        pid_t pid = fork();

        if (pid == 0) {

            dup2(in, 0);

            if (i != cmds.size() - 1)
                dup2(fd[1], 1);

            close(fd[0]);

            stringstream ss(cmds[i]);
            vector<string> args;
            string word;

            while (ss >> word)
                args.push_back(word);

            char** argv = convert(args);

            execvp(argv[0], argv);

            perror("Pipe Error");
            exit(1);
        }

        wait(nullptr);

        close(fd[1]);

        in = fd[0];
    }
}

int main() {

    signal(SIGINT, signalHandler);

    string input;

    while (true) {

        cout << "myshell> ";

        getline(cin, input);

        if (input.empty())
            continue;

        historyList.push_back(input);

        if (input == "exit")
            break;

        if (input == "pwd") {

            char cwd[1024];

            getcwd(cwd, sizeof(cwd));

            cout << cwd << endl;

            continue;
        }

        if (input.substr(0,2) == "cd") {

            string path = input.substr(3);

            if (chdir(path.c_str()) != 0)
                perror("cd");

            continue;
        }

        if (input == "history") {

            for (int i = 0; i < historyList.size(); i++)
                cout << i + 1 << " " << historyList[i] << endl;

            continue;
        }

        if (input.find('|') != string::npos) {
            executePipe(input);
            continue;
        }

        stringstream ss(input);

        vector<string> args;

        string word;

        while (ss >> word)
            args.push_back(word);

        execute(args);
    }

    return 0;
}
