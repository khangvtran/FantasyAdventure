//
//  main.cpp
//  Character

#include <iostream>
#include <string>

# include "Character.h"

using namespace std;

const string commands[] = {"move north", "move south", "move west", "move east",
                                "attack" };
const int numCommands = 5;


bool isValidCommand(string command);
void doCommand(string command, Character* c) throw(string);

int main() {
    Character* c;
    
    cout << "Enter a name: ";
    string name;
    cin >> name;
    
    string command;
    do {
        
        cin >> command;
        try {
            if(isValidCommand(command))
                doCommand(command, c);
        } catch (string exception) {
            cerr << exception << endl;
        }
    } while(true);
}

bool isValidCommand(string command)
{
    for(int i = 0; i < numCommands; i++)
    {
        if(command == commands[i])
            return true;
    }
    return false;
}

void doCommand(string command, Character* c) throw(string)
{
    if(command == commands[0])
        c->moveNorth();
    else if(command == commands[1])
        c->moveSouth();
}



