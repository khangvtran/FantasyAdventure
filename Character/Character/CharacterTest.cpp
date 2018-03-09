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
#include "Dungeon.h"
#include "Character.h"
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include <string>
using namespace std;

const int ROWS = 10;
const int COLS = 10;

const string commands[] = {"move", "attack", "drop", "pickup", "activate", "use", "print", "/"};
const int NUM_COMMANDS = 8;
const string INTRO = "AdventureGame \n\nWelcome to the phantasy adventure game! In search for riches and personal glory you have arrived at this\ndark and abandoned dungeon full of dragons and other creatures that lurk from around all corners ready to attack you and stall your journey for greatness. To find the treasure you will have to navigate through a labyrinth and slay monsters. Along the way you will find useful hints that will guide you toward the room with the treasure as well as maps that will show you your location in relation to the treasure room. You will collect items that will help you recover, kill monsters, and move closer to your goal. \n\nYou have 3 lives. Use them wisely!\n\n";
bool isInvalidChar(int i);

bool isValidCommand(string& command);
void doCommand(const string& command, Character* c) throw(/*const char*,*/ AdventureErrors::InvalidMove, AdventureErrors::MissingObject, AdventureErrors::CharacterDeath);

int main(void)
{
    bool replay = true;
    bool restart = true;
    srand(time(0));
    Dungeon* dungeon = nullptr;
    Character* c = nullptr;
    string command;
    do {
        if(restart)
        {
            cout << INTRO;
            
            //Create a Dungeon
             dungeon = new Dungeon(ROWS, COLS);
            
            cout << "Enter a name: ";
            string name;
            getline(cin, name);
            
            //Create a Character
            c = new Character(name, ROWS, COLS, *dungeon);
            restart = false;
        }
        // Enter
        cout << "Enter command: ";
        getline(cin, command);
        try {
            //dungeon->printMap(c->getRowPos(), c->getColPos(), Dungeon::BASIC);
            //dungeon->printMap(c->getRowPos(), c->getColPos(), Dungeon::MONSTER);
            //dungeon->printMap(c->getRowPos(), c->getColPos(), Dungeon::ROOMOBJECT);
            //dungeon->printMap(c->getRowPos(), c->getColPos(), Dungeon::ITEM);
            //dungeon->printMap(c->getRowPos(), c->getColPos(), Dungeon::ALL);

             //c.printRoom();
            if(isValidCommand(command))
                doCommand(command, c);
            else
                cerr << "that wasn't a valid command" << endl;
            
            cout << endl;
            cout << "X: " << c->getRowPos() << " Y: " << c->getColPos() << endl;
            
        }/* catch (const char* &exception) {
            cerr << exception << endl;
        }*/
        catch (AdventureErrors::InvalidMove &err)
        {
            cerr << err.what() << endl;
        }
        catch(AdventureErrors::MissingObject &err)
        {
            cerr << err.what() << endl;
        }
        catch(AdventureErrors::CharacterDeath &err)
        {
            cerr << err.what() << endl;
            char again;
            do
            {
                cout << "Did you wish to play again? (Y/N): ";
                cin >> again;
                if(again == 'n' || again == 'N')
                {
                    cout << "Goodbye " << c->getName() << "!" << endl;
                    replay = false;
                }
                else
                {
                    restart = true;
                    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; // 20 newlines?
                }
                
            } while(!(again != 'y' || again != 'Y' || again != 'n' || again != 'N'));
            cin.clear();
            cin.ignore(10, '\n');
            delete dungeon;
            delete c;
        }
        cin.clear();
    } while(replay);
    
    return 0;
}

bool isInvalidChar(int i)
{
    return !(::isalnum(i) || ::isspace(i) || i == '/');
}
bool isValidCommand(string& command)
{
    command.erase(remove_if (command.begin(), command.end(), isInvalidChar), command.end());
    string firstWord = command.substr(0, command.find(" "));
    cout << command << endl;
    for(int i = 0; i < NUM_COMMANDS-1; i++)
    {
        if(firstWord == commands[i])
            return true;
    }
    if(command.substr(0,1) == commands[NUM_COMMANDS-1])
        return true;
    return false;
}

void doCommand(const string &command, Character *c) throw(/*const char*,*/ AdventureErrors::InvalidMove, AdventureErrors::MissingObject, AdventureErrors::CharacterDeath)
{
    size_t spacePos = command.find(" ");
    string cmd = command.substr(0, spacePos);
    
    try {
        if(cmd == commands[0]) // move
            c->move(command.substr(spacePos+1));
        else if(cmd == commands[1]) // attack
            c->attack();
        else if(cmd == commands[2]) // drop
            c->dropItem(command.substr(spacePos+1));
        else if(cmd == commands[3]) // pickup
            c->pickupItem(command.substr(spacePos+1));
        else if(cmd == commands[4]) // activate
            c->activate(command.substr(spacePos+1));
        else if(cmd == commands[5]) // use item
            c->useItem(command.substr(spacePos+1));
        else if(cmd == commands[6]) // print attributes
            c->print();
        else if(cmd.substr(0,1) == commands[NUM_COMMANDS-1]) // cheat
            c->cheat(command.substr(1,spacePos-1), command.substr(spacePos+1)); // possible cheat commands, "/god" and "/tp x y" without quotes, x y should be ints. to be implemented -> print map, spawn items into inv/equipment
        
        else;
    }
    //catch(const char*) { throw; }
    catch(AdventureErrors::InvalidMove) { throw; }
    catch(AdventureErrors::MissingObject) { throw; }
    catch(AdventureErrors::CharacterDeath) { throw; }
}
