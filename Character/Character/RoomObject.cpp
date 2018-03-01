#define _CRT_SECURE_NO_WARNINGS

#include <iomanip>
#include <iostream>
#include <string.h>
#include "RoomObject.h"
/**************************************************************************
 RoomObject class (base class)
 ****************************************************************************/
RoomObject::RoomObject(string name, string description) :name(name), description(description){
}
void RoomObject::setName(string name) {
    name = name;
}
string  RoomObject::getName() const {
    return name;
}
void  RoomObject::setDescription(string description) {
    description = description;
}
string  RoomObject::getDescription() const{
    return  description;
}
/***********************************************************************************
 book class (derive from RoomObject class)
 Using for giving player one of five randomized hints about the game.
 1 you need to find the Ruby and other four thing to complete the game.
 2 you need to find the Sapphire to and other four thing to complete the game.
 3 you need to find the Emerald to and other four thing to complete the game.
 4 you need to slay the Boss Monster and dong other four thing to complete the game.
 5 you need to activate the Treasure Room and do other four thing to complete the game.
 ***********************************************************************************/

Book::Book(string name, string description) : RoomObject(name, description) {}
void Book::use() const {
    
    cout << "congratulates! A hints book in this room!!!" << std::endl;
    
    
    std::cout << "Greedy man! You need to find the Ruby,  Sapphire, Emerald, Treasure and" << std::endl;
    std::cout <<" slay the boss monster to WIN THE GAME!!!!! COME ON!!!!" << std::endl;
    
}
/***********************************************************************************
 Flare class (derive from RoomObject class)
 Using for diplay the adjacent four rooms' object and it is more easy for play to
 which room she/he want to get in.
 ***********************************************************************************/
Flare::Flare(string name, string description) :RoomObject(name, description) {}
void Flare::use() const {
    std::cout << "Wow! man, there is a flare in this room, you can use" << std::endl;
    std::cout << "it to look each object of adjacent four room. Think wisely before taking action!!!" << std::endl;
}
/***********************************************************************************
 Fountain class (derive from RoomObject class)
 Using for increase or decrease player Health when player drink it.
 Plan to +3 or -3.
 ***********************************************************************************/
Fountain::Fountain(string name, string description) :RoomObject(name, description) {}
void Fountain::use() const {
    cout << "This fountain can increase your helth, ... or else.";
}
/***********************************************************************************
 Treasure class (derive from RoomObject class)
 Activate the treasure room.
 Player win the game if he/she have already got the other four thing(Ruby, Sapphire, Emerald
 and slay the Boss Monster).
 ***********************************************************************************/

Treasure::Treasure(string name, string description) :RoomObject(name, description) {}
void Treasure::use() const {
    std::cout << "Brave man, have you got Ruby, Sapphire, Emerald and" << std::endl;
    std::cout << "slay the Boss Monster, then you win the adventure!!!! CONGRATUATIONS!!!!!!!" << std::endl;
    
}
/***********************************************************************************
 Map class (derive from RoomObject class)
 Using for telling player  which room is treasure room.
 ***********************************************************************************/
Map::Map(string name, string description) :RoomObject(name, description) {}
void Map::use() const {
    std::cout << "Well! There is a map hanging on the corner! Go and check it" << std::endl;
    std::cout << "to see which room have treasure!!! Lucky man!!!" << std::endl;
    
}


