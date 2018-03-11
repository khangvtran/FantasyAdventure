/*
 
 Implementation file for the RoomObject class.
 
 */

#include <iomanip>
#include <iostream>
#include <string>
#include "RoomObject.h"

/**************************************************************************
 RoomObject's Constructor
 Initiaizes Room Object data to starting values.
 **************************************************************************/
RoomObject::RoomObject(string n, string d) :name(n), description(d) {}

/**************************************************************************
 setName
 Sets Room Object's name.
 **************************************************************************/
void RoomObject::setName(string n)
{
    name = name;
}

/**************************************************************************
 getName
 Returns Room Object's name.
 **************************************************************************/
string RoomObject::getName() const
{
    return name;
}

/**************************************************************************
 setDescription
 Sets Room Object's description.
 **************************************************************************/
void  RoomObject::setDescription(string d)
{
    description = description;
}

/**************************************************************************
 getDescription
 Returns Room Object's description.
 **************************************************************************/
string  RoomObject::getDescription() const
{
    return  description;
}

/**************************************************************************
 use
 Prints useful hints on how to win the game.
 **************************************************************************/
Book::Book(string name, string description) : RoomObject(name, description) {}
void Book::use() const
{
    cout << endl;
    cout << "You open the book and find the following hints: " << endl;
    cout << "Hint #1: You need to find 3 gems: Ruby, Sapphire and Emerald to win the game!" << endl;
    cout << "Hint #2: You need to kill the dragon boss to acquire the treasure." << endl;
    cout << "Hint #3: Save the kill scroll for the dragon boss." << endl;
    cout << endl;
}

/**************************************************************************
 use
 Prints a message that it is being used.
 **************************************************************************/
Flare::Flare(string name, string description) :RoomObject(name, description) {}
void Flare::use() const
{
    cout << endl;
    cout << "You've lit the flare. This is what you can see in four adjacent rooms:" << endl;
    cout << endl;
   
}
/**************************************************************************
 use
 Prints a message that it is being used.
 **************************************************************************/
Fountain::Fountain(string name, string description) : RoomObject(name, description) {}
void Fountain::use() const
{
    cout << endl;
    cout << "You take a sip from the fountain and ..." << endl;
    cout << endl;
}

/**************************************************************************
 use
 Prints a message that it is being used.
 **************************************************************************/
Map::Map(string name, string description) :RoomObject(name, description) {}
void Map::use() const
{
    cout << "Looking at the map you see this: " << endl;
}

/**************************************************************************
 use
 Prints that the treasure was used.
 **************************************************************************/
Treasure::Treasure(string name, string description) :RoomObject(name, description) {}
void Treasure::use() const
{
    std::cout << "Congratulation! You won the game!" << std::endl;
}



