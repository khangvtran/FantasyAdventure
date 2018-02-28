/*
 
 AdventureGame
 
 Welcome to the phantasy adventure game! In search for riches and personal glory you have arrived at this
 dark and abandoned dungeon full of dragons and other creatures that lurk from around all corners ready to
 attack you and stall your journey for greatness.
 To find the treasure you will have to navigate through a labyrinth and slay monsters.
 Along the way you will find useful hints that will guide you toward the room with the treasure as well as
 maps that will show you your location in relation to the treasure room. You will collect items that
 will help you recover, kill monsters, and move closer to your goal. You have 3 lives.
 Use them wisely!
 
 
 //ADD
 -> Print attributes
 -> Attribute allocation
 -> Help menu
 
 */

#include <iostream>
#include "Dungeon.hpp"
#include "Character.h"
#include <cstdlib>
using namespace std;

const int ROWS = 3;
const int COLS = 3;

const string commands[] = {"move north", "move south", "move west", "move east",
    "attack" };
const int numCommands = 5;
const string INTRO = "AdventureGame \n\nWelcome to the phantasy adventure game! In search for riches and personal glory you have arrived at this\ndark and abandoned dungeon full of dragons and other creatures that lurk from around all corners ready to attack you and stall your journey for greatness. To find the treasure you will have to navigate through a labyrinth and slay monsters. Along the way you will find useful hints that will guide you toward the room with the treasure as well as maps that will show you your location in relation to the treasure room. You will collect items that will help you recover, kill monsters, and move closer to your goal. \n\nYou have 3 lives. Use them wisely!\n\n";
bool isValidCommand(string &command);
void doCommand(string &command, Character &c) throw(string);

int main(void )
{
    srand(time(0));
    cout << INTRO;
    
    //Create a Dungeon
    Dungeon dungeon(ROWS, COLS);
    
    cout << "Enter a name: ";
    string name;
    getline(cin, name);
    
    //Create a Character
    Character c(name, ROWS, COLS, dungeon);
    
    //Enter
    string command;
    do {
        
        cout << "Enter command: ";
        getline(cin, command);
        try {
            if(isValidCommand(command))
                doCommand(command, c);
            cout << endl;
            cout << "X: " << c.getXPos() << " Y: " << c.getYPos() << endl;
            dungeon.printMap(c.getXPos(), c.getYPos());
            cout << endl;
            
        } catch (string exception) {
            cerr << exception << endl;
        }
    } while(true);
    
    return 0;
}

bool isValidCommand(string &command)
{
    for(int i = 0; i < numCommands; i++)
    {
        if(command == commands[i])
        {
            cout << "That was a valid command" << endl;
            return true;
        }
    }
    return false;
}

void doCommand(string &command, Character &c) throw(string)
{
    if(command == commands[0])
        c.moveNorth();
    else if(command == commands[1])
        c.moveSouth();
    else if(command == commands[2])
        c.moveWest();
    else if(command == commands[2])
        c.moveEast();
    else
                ;
}
