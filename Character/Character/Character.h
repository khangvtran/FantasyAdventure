//
//  Character.hpp
//  Character
//
//  Created by Khang Tran on 2/2/18.
//  Copyright © 2018 Khang Tran and Joshua Kuan. All rights reserved.
//

#ifndef Character_h
#define Character_h

#include <stdio.h>

# include <iostream>
# include <string>
# include <iomanip>
# include <cstdlib>

#include <unordered_map>
#include <vector>

using namespace std;

# include "Item.h"
//# include "Equipment.h"
# include "Dungeon.h"
# include "Room.h"
# include "LinkedList.h"
# include "RoomObject.h"

class Character
{
private:
    string name;
    int health;
    int strength;
    int intelligence;
    int luck;
    bool alive = true;
    int lives;
    
    List<Item*> itemList;
    unordered_map<string, Equipment*> equipmentSet;
    
    Dungeon* dungeon;
    Room* currentRoom;
    struct Location
    {
        const int xBound;
        const int yBound;
        int xPos;
        int yPos;
        Location(int xb, int yb) : xBound(xb), yBound(yb) {}
    };

    Location location; // instantiate an inner object from struct location
    
    void _moveNorth() throw(const char*);
    void _moveSouth() throw(const char*);
    void _moveEast() throw(const char*);
    void _moveWest() throw(const char*);
    
public:
    
    
    
    /* Constructor */
    /**
     * name is assigned for character name.
     * row refers to the MAX bound of rows in the dungeon.
     * col refers to the MAX bound of cols in the dungeon.
     * dungeon is a reference which gets stored to use for the dungeon pointer.
     */
    Character(string, int, int, Dungeon&);
    
    /* Destructor */
    
    
    /* Accessor */
    string getName() const;
    int getHealth() const;
    int getStrength() const;
    int getIntelligence() const;
    int getLuck() const;
    bool isAlive() const;
    int getXPos() const;
    int getYPos() const;
    
    
    /* Manipulator */
    void setInitialAttributes();
    void setName(string Name);
    void setHealth(int Health);
    void setStrength(int Strength);
    void setIntelligence(int Intelligence);
    void setLuck(int Luck);
    void die();
    void setXPos(int X);
    void setYPos(int Y);
    
    
    /* Interaction with Items - Equipment */
    
    void pickupItem(string item);    // CHANGE: swapEquipment is now a part of this
    void dropItem(string item);
    void useItem(string item);       // CHANGE: Implementation: How do we create a dummy item pointer then check it

    
    /* Interactions with Monsters */
    //void useSpecialAbility();
    void attack();
    bool HitOrHeal();
    
    /* Ineraction with RoomObjects */
    void readBook() const;
    void readMap() const;
    void useFlare() const;
    void drinkFromFountain();
    void activateEndgameTreasure() const;

    
    /* Moving */
    void move(string direction) throw(const char*);
    
    void activate(string thing);
    
};



#endif /* Character_hpp */








