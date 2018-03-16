/*
 
 Implementation file for the RoomObject class.
 
 */


#include <iostream>
#include <string>
#include "RoomObject.h"

/**************************************************************************
 RoomObject's Constructor
 Initiaizes Room Object data to starting values.
 **************************************************************************/
RoomObject::RoomObject(std::string n, std::string d) :name(n), description(d) {}

/**************************************************************************
 setName
 Sets Room Object's name.
 **************************************************************************/
void RoomObject::setName(std::string n)
{
    name = name;
}

/**************************************************************************
 getName
 Returns Room Object's name.
 **************************************************************************/
std::string RoomObject::getName() const
{
    return name;
}

/**************************************************************************
 setDescription
 Sets Room Object's description.
 **************************************************************************/
void  RoomObject::setDescription(std::string d)
{
    description = description;
}

/**************************************************************************
 getDescription
 Returns Room Object's description.
 **************************************************************************/
std::string RoomObject::getDescription() const
{
    return  description;
}

/**************************************************************************
 use
 Prints useful hints on how to win the game.
 **************************************************************************/
Book::Book(std::string name, std::string description) : RoomObject(name, description) {}
void Book::use() const
{
    std::cout << std::endl;
    std::cout << "You open the book and find the following hints: " << std::endl;
    std::cout << "Hint #1: You need to find 3 gems: Ruby, Sapphire and Emerald to win the game!" << std::endl;
    std::cout << "Hint #2: You need to kill the dragon boss to acquire the treasure." << std::endl;
    std::cout << "Hint #3: Save the kill scroll for the dragon boss." << std::endl;
    std::cout << std::endl;
}

/**************************************************************************
 use
 Prints a message that it is being used.
 **************************************************************************/
Flare::Flare(std::string name, std::string description) :RoomObject(name, description) {}
void Flare::use() const
{
    std::cout << std::endl;
    std::cout << "You've lit the flare. This is what you can see in four adjacent rooms:" << std::endl;
    std::cout << std::endl;
   
}
/**************************************************************************
 use
 Prints a message that it is being used.
 **************************************************************************/
Fountain::Fountain(std::string name, std::string description) : RoomObject(name, description) {}
void Fountain::use() const
{
    std::cout << std::endl;
    std::cout << "You take a sip from the fountain and ..." << std::endl;
    std::cout << std::endl;
}

/**************************************************************************
 use
 Prints a message that it is being used.
 **************************************************************************/
Map::Map(std::string name, std::string description) :RoomObject(name, description) {}
void Map::use() const
{
    std::cout << "Looking at the map you see this: " << std::endl;
}

/**************************************************************************
 use
 Prints that the treasure was used.
 **************************************************************************/
Treasure::Treasure(std::string name, std::string description) :RoomObject(name, description) {}
void Treasure::use() const
{
    std::cout << "Congratulation! You won the game!" << std::endl;
}



