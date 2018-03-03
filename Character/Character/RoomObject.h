//#pragma once
#ifndef RoomObject_h
#define RoomObject_h

#include <iostream>
#include <string>
//#include "RoomObject.h"
using namespace std;
/**************************************************************************
 RoomObject class (base class)
 ****************************************************************************/
class RoomObject
{
protected:
    string name, description;
public:
    RoomObject() {};
    RoomObject(string name, string description);
    
    void setName(string name);
    string  getName() const;
    void  setDescription(string decreiption);
    string  getDescription() const;
    virtual void use() const = 0;
    virtual ~RoomObject() {};
    
};
/***********************************************************************************
 book class (derive from RoomObject class)
 Using for giving player one of five randomized hints about the game.
 1 you need to find the Ruby and other four thing to complete the game.
 2 you need to find the Sapphire to and other four thing to complete the game.
 3 you need to find the Emerald to and other four thing to complete the game.
 4 you need to slay the Boss Monster and dong other four thing to complete the game.
 5 you need to activate the Treasure Room and do other four thing to complete the game.
 ***********************************************************************************/
class Book : public RoomObject {
public:Book(string n, string d);
    ~Book() {};
    void use() const;
};
/***********************************************************************************
 Flare class (derive from RoomObject class)
 Using for diplay the adjacent four rooms' object and it is more easy for play to
 which room she/he want to get in.
 ***********************************************************************************/
class Flare : public RoomObject {
public:Flare(string n, string d);
    ~Flare() {};
    void use() const;
    
};
/***********************************************************************************
 Fountain class (derive from RoomObject class)
 Using for increase or decrease player Health when player drink from it.
 Plan to +3 or -3.
 ***********************************************************************************/
class Fountain : public RoomObject {
public:Fountain(string n, string d);
    ~Fountain() {};
    void use() const;
};
/***********************************************************************************
 Treasure class (derive from RoomObject class)
 Activate the treasure room.
 Player win the game if he/she have already got the other four thing(Ruby, Sapphire, Emerald
 and slay the Boss Monster).
 ***********************************************************************************/
class Treasure : public RoomObject {
public:Treasure(string n, string d);
    ~Treasure() {};
    void use() const;
};
/***********************************************************************************
 Map class (derive from RoomObject class)
 Using for telling player  which room is a treasure room.
 ***********************************************************************************/
class Map : public RoomObject {
public:Map(string n, string d);
    ~Map() {};
    void use() const;
    
};
#endif

