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
using namespace std;

# include "LinkedList.h"

class Character
{
private:
    string name;
    int health;
    int strength;
    int intelligence;
    int luck;
    bool alive = true;
    // List<items> itemList;
    // set<equipments> equipmentSet;
    
    struct Location
    {
        int xPos;
        int yPos;
    };
    // Josh added comment
    Location location; // instantiate an inner object from struct location
public:
    /* Constructor*/
    Character(string Name, int row, int col) : name(Name)
    {
        // still need to implement math for determining base stats for each subclass
        setXPos(row-1);
        setYPos(rand() % col);
    }
    
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
    void setName(string Name);
    void setHealth(int Health);
    void setStrength(int Strength);
    void setIntelligence(int Intelligence);
    void setLuck(int Luck);
    void die();
    void setXPos(int X);
    void setYPos(int Y);
    
    
    /* Other operations */
    
    // void pickupItem(items item);
    // void dropItem(items item)
    // void useItem(items item);
    // virtual void swapEquipment(equipments equipment) = 0;
    // void attack(monsters monster) = 0;
    virtual void useSpecialAbility() = 0;
    void move(char * moveCommand);
};



#endif /* Character_hpp */








