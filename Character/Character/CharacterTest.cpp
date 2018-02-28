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

const string commands[] = {"move", "attack", "drop", "pickup" };
const int numCommands = 3;
const string INTRO = "AdventureGame \n\nWelcome to the phantasy adventure game! In search for riches and personal glory you have arrived at this\ndark and abandoned dungeon full of dragons and other creatures that lurk from around all corners ready to attack you and stall your journey for greatness. To find the treasure you will have to navigate through a labyrinth and slay monsters. Along the way you will find useful hints that will guide you toward the room with the treasure as well as maps that will show you your location in relation to the treasure room. You will collect items that will help you recover, kill monsters, and move closer to your goal. \n\nYou have 3 lives. Use them wisely!\n\n";
bool isValidCommand(string &command);
void doCommand(string &command, Character &c) throw(const char*);

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
             //c.printRoom();
            if(isValidCommand(command))
                doCommand(command, c);
            else
                cout << "that wasn't a valid command" << endl;
            cout << endl;
            cout << "X: " << c.getXPos() << " Y: " << c.getYPos() << endl;

            //dungeon.printMap(c.getXPos(), c.getYPos());
            //c.printRoom();
            
        } catch (const char* exception) {
            cerr << exception << endl;
        }
    } while(true);
    
    return 0;
}

bool isValidCommand(string &command)
{
    string firstWord = command.substr(0, command.find(" "));
    //cout << firstWord;
    for(int i = 0; i < numCommands; i++)
    {
        if(firstWord == commands[i])
            return true;
    }
    return false;
}

void doCommand(string &command, Character &c) throw(const char*)
{
    size_t spacePos = command.find(" ");
    string cmd = command.substr(0, spacePos);
    
    try {
        if(cmd == commands[0]) // move
            c.move(command.substr(spacePos+1));
        else if(cmd == commands[1]) // attack
            c.attack();
        else if(cmd == commands[2]) // drop
            c.dropItem(command.substr(spacePos+1));
        else if(cmd == commands[3])
            c.pickupItem(command.substr(spacePos+1));
        else;
    }
    catch(const char*) {
        throw;
    }
    
}
