//
//  Character.hpp
//  Character
//
//  Created by Khang Tran on 2/2/18.
//  Copyright © 2018 Khang Tran and Joshua Kuan. All rights reserved.
//



#ifndef Character_h
#define Character_h

#include <iostream>
#include <string>

#include <unordered_map>
#include <vector>

using namespace std;

#include "Item.h"
#include "Dungeon.h"
#include "Room.h"
#include "LinkedList.h"
#include "RoomObject.h"
#include "Exceptions.h"

class Character
{
private:
    string name;
    int maxHealth;
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
        int row; // y coord
        int col; // x coord
        Location(const int &xb = 0, const int &yb = 0) : xBound(xb) ,yBound(yb) {}
    };

    Location* location; // instantiate an inner object from struct location
    
    /** Private Helper Functions **/
    
    void _die();
    bool _randomizer() const;
    void _printAttributes() const;
    void _printInventory() const;
    void _printEquipmentSet() const;
    
    void _useKillScroll();
    int equipmentHealth() const;
    
    /* Helper move functions */
    void _moveNorth() throw(AdventureErrors::InvalidMove);
    void _moveSouth() throw(AdventureErrors::InvalidMove);
    void _moveEast() throw(AdventureErrors::InvalidMove);
    void _moveWest() throw(AdventureErrors::InvalidMove);
    
    /* Interaction with RoomObjects */
    void _readBook() const throw(AdventureErrors::MissingObject);
    void _readMap() const throw(AdventureErrors::MissingObject);
    void _useFlare() const throw(AdventureErrors::MissingObject);
    void _drinkFromFountain() throw(AdventureErrors::MissingObject);
    void _activateEndgameTreasure() const throw(AdventureErrors::MissingObject, AdventureErrors::CharacterDeath);
    
public:
    
    /* Constructor */
    /**
     * name is assigned for character name.
     * row refers to the MAX bound of rows in the dungeon.
     * col refers to the MAX bound of cols in the dungeon.
     * dungeon is a reference which gets stored to use for the dungeon pointer.
     */
    Character(const string&, const int&, const int&, Dungeon&);
    
    /* Destructor */
    
    ~Character();
    
    /* Accessor */
    string getName() const;
    
    int getHealth() const;
    int getMaxHealth() const;
    int getStrength() const;
    int getIntelligence() const;
    int getLuck() const;
    bool isAlive() const;
    
    int getRowPos() const;
    int getColPos() const;
    
    
    /* Manipulator */
    void setInitialAttributes(const int&);
    void setName(const string&);
    void setMaxHealth(const int&);
    void setHealth(const int&);
    void setStrength(const int&);
    void setIntelligence(const int&);
    void setLuck(const int&);

    void setRowPos(const int&);
    void setColPos(const int&);
    
    
    /* Interaction with Items - Equipment */
    
    void pickupItem(const string& item);    // CHANGE: swapEquipment is now a part of this
    void dropItem(const string& item);
    void useItem(const string& item);       // CHANGE: Implementation: How do we create a dummy item pointer then check it
    
    
    /* Interactions with Monsters */
    //void useSpecialAbility();
    void attack() throw(AdventureErrors::CharacterDeath);
    
    /* Moving */
    void move(const string&) throw(AdventureErrors::InvalidMove);
    
    void activate(const string&) throw(AdventureErrors::MissingObject, AdventureErrors::CharacterDeath);
    void print() const;
    
    /* Cheat */
    void cheat(const string&, const string& = "");
};



#endif /* Character_hpp */








