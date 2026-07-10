#include "history.h"

#include <iostream>
#include <vector>

using namespace std;

// Stores command history
static vector<string> historyList;

void addHistory(const string& command)
{
    historyList.push_back(command);
}

void showHistory()
{
    if(historyList.empty())
    {
        cout << "No commands in history.\n";
        return;
    }

    for(size_t i = 0; i < historyList.size(); i++)
    {
        cout << i + 1 << "  "
             << historyList[i]
             << endl;
    }
}