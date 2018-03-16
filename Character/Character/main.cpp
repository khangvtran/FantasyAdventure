/*
 
 PhantasyAdventure
 
 This simulation is a phantasy quest for a treasure.
 You must navigate through the dungeon's labyrinth, collect three gems and kill the dragon boss to win your riches.
 Along the way, you will collect potions that heal you, equipment that strenghtens you and find maps, books and other
 objects that will help guide you toward your destination. You can also attack monsters and unlock more items of value.
 
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

const string commands[] = {"attack", "activate", "drop", "move", "pickup", "print", "use", "help", "quit", "/"};
const int NUM_COMMANDS = 10;
const string HELP_FILE = "help.bin";
const string INTRO = "AdventureGame \n\nWelcome to the phantasy adventure game! In search for riches and personal glory you have arrived at this dark and abandoned\ndungeon full of dragons and other creatures that lurk from around all corners ready to attack you and stall your journey for greatness. To find the treasure you will have to navigate through a labyrinth and slay monsters. Along the way you will find\nuseful hints that will guide you toward the room with the treasure as well as maps that will show you your location in\nrelation to the treasure room. You will collect items that will help you recover, kill monsters, and move closer to your goal.\n\nYou have 3 lives. Use them wisely!\n\n";
bool again(Character*&);
void initialize(Dungeon*&, Character*&, ifstream&);
bool isInvalidChar(int i);
void displayHelpScreen(ifstream&, const string& = "help");
bool isValidCommand(string& command);
void doCommand(const string& command, Character*& c, ifstream&) throw(AdventureErrors::InvalidMove, AdventureErrors::MissingObject, AdventureErrors::CharacterDeath);

int main(void)
{
    
    ifstream helpFile(HELP_FILE.c_str(), ios::in | ios::binary);
    bool replay = true;
    bool restart = true;
    srand(time(0));
    Dungeon* dungeon = nullptr;
    Character* c = nullptr;
    string command;
    do
    {
        if(restart)
        {
            cout << INTRO;
            initialize(dungeon, c, helpFile);
            restart = false;
        }
        cout << "Enter command: ";
        getline(cin, command);
        try
        {
            if(isValidCommand(command))
                doCommand(command, c, helpFile);
            else
                cerr << "Uh oh, that didn't seem like a valid command. You can type 'help' at any time to bring up the help menu." << endl;
        }
        catch (AdventureErrors::InvalidMove &err)
        {
            cerr << err.what() << endl << endl;
        }
        catch(AdventureErrors::MissingObject &err)
        {
            cerr << err.what() << endl << endl;
        }
        catch(AdventureErrors::CharacterDeath &err)
        {
            restart = true;
            cerr << err.what() << endl << endl;
            replay = again(c); // if player wants to replay (true)
            delete dungeon;
            delete c;
            cin.clear();
            cin.ignore(10, '\n');
        }
        cin.clear();
    } while(replay);
    
    return 0;
}


bool again(Character* &c)
{
    char replay;
    do
    {
        cout << "Did you wish to play again? (Y/N): ";
        cin >> replay;
        if(replay == 'n' || replay == 'N')
        {
            cout << "Goodbye " << c->getName() << "!" << endl;
            return false;
        }
        
    } while(!(replay != 'y' || replay != 'Y' || replay != 'n' || replay != 'N'));
    return true;
}

void initialize(Dungeon* &d, Character* &c, ifstream& helpFile)
{
    try
    {
        if(!helpFile.is_open())
            throw AdventureErrors::FileOpenError(HELP_FILE.c_str());
    }
    catch (AdventureErrors::FileOpenError &err) {
        string newFile;
        cerr << err.what() << endl;
        helpFile.clear();
        cout << "Enter another file: ";
        getline(cin, newFile);
        helpFile.open(newFile.c_str(), ios::in | ios::binary);
        if (!helpFile)
        {
            cout << "File Open Error" << endl;
            exit(EXIT_FAILURE);
        }
    }
    
    //Create a Dungeon
    d = new Dungeon{ROWS, COLS};
    
    cout << "Enter a name: ";
    string name;
    getline(cin, name);
    
    //Create a Character
    c = new Character{name, ROWS, COLS, *d};
}

bool isInvalidChar(int i)
{
    return !(::isalnum(i) || ::isspace(i) || i == '/');
}

bool isValidCommand(string& command)
{
    command.erase(remove_if (command.begin(), command.end(), isInvalidChar), command.end());
    string firstWord = command.substr(0, command.find(" "));
    for(int i = 0; i < NUM_COMMANDS-1; i++)
    {
        if(firstWord == commands[i])
            return true;
    }
    if(command.substr(0,1) == commands[NUM_COMMANDS-1])
        return true;
    return false;
}

void displayHelpScreen(ifstream& input, const string& command)
{
    input.clear();
    input.seekg(0, ios::beg);
    int cursor = 0;
    int numLines = 0;
    if(isdigit(command[0]) || command == "help")
    {
        int pageNum = isdigit(command[0]) ? command[0] - '0' : 1;
        if(pageNum <= 0 || pageNum > 3)
        {
            cerr << "There is no such help page. Type 'help' to view the help menu." << endl;
            return;
        }
        
        if(pageNum > 0 && pageNum <= 3)
        {
            for(int i = 0; i < pageNum; i++)
            {
                input.read(reinterpret_cast<char*>(&cursor), 4);
                input.read(reinterpret_cast<char*>(&numLines), 4);
            }
            input.seekg(cursor, ios::beg);
            string str;
            int lengthOfStr;
            for(int i = 0; i < numLines; i++)
            {
                input.read(reinterpret_cast<char*>(&lengthOfStr), 4);
                str.resize(lengthOfStr);
                input.read(reinterpret_cast<char*>(&str[0]), lengthOfStr);
                cout << str << endl;
            }
            cout << endl;
            return;
        }
    }
    else
    {
        input.clear();
        int counter = 0;
        for(int i = 0; i < NUM_COMMANDS - 2; i++)
        {
            if(command != commands[i])
                counter++;
            else
                break;
        }
        if(counter == NUM_COMMANDS - 2)
            cerr << "There is no such help page. Type 'help' to view the help menu." << endl;
        else
        {
            input.seekg(0, ios::beg);
            input.clear();
            for(int i = 0; i < counter+4; i++)
            {
                input.read(reinterpret_cast<char*>(&cursor), 4);
                input.read(reinterpret_cast<char*>(&numLines), 4);
            }
            input.seekg(cursor, ios::beg);
            string str;
            int lengthOfStr;
            for(int i = 0; i < numLines; i++)
            {
                input.read(reinterpret_cast<char*>(&lengthOfStr), 4);
                str.resize(lengthOfStr);
                input.read(reinterpret_cast<char*>(&str[0]), lengthOfStr);
                cout << str << endl;
            }
            cout << endl;
            return;
        }
    }
}
void doCommand(const string &command, Character *&c, ifstream& helpFile) throw(/*const char*,*/ AdventureErrors::InvalidMove, AdventureErrors::MissingObject, AdventureErrors::CharacterDeath)
{
    size_t spacePos = command.find(" ");
    string cmd = command.substr(0, spacePos);
    
    try
    {
        if (cmd == commands[0]) // attack
            c->attack();
        else if(cmd == commands[1]) // activate
            c->activate(command.substr(spacePos+1));
        else if(cmd == commands[2]) // drop
            c->dropItem(command.substr(spacePos+1));
        else if(cmd == commands[3]) // move
                c->move(command.substr(spacePos+1));
        else if(cmd == commands[4]) // pickup
            c->pickupItem(command.substr(spacePos+1));
        else if(cmd == commands[5]) // print attributes
            c->print();
        else if(cmd == commands[6]) // use item
            c->useItem(command.substr(spacePos+1));
        else if(cmd == commands[7])
            displayHelpScreen(helpFile, command.substr(spacePos+1));
        else if(cmd == commands[8])
            throw AdventureErrors::CharacterDeath("Aww, quiting already?");
        else if(cmd.substr(0,1) == commands[NUM_COMMANDS-1]) // cheat
            c->cheat(command.substr(1,spacePos-1), command.substr(spacePos+1)); // possible cheat commands, "/god" and "/tp x y" without quotes, x y should be ints. to be implemented -> print map, spawn items into inv/equipment
        else;

    }
    catch(AdventureErrors::InvalidMove) { throw; }
    catch(AdventureErrors::MissingObject) { throw; }
    catch(AdventureErrors::CharacterDeath) { throw; }
}
