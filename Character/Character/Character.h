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
using namespace std;

# include "Dungeon.hpp"
# include "Room.hpp"
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
    unordered_map<string, Equipment> equipmentSet;
    Dungeon* dungeon;
    Room* currentRoom;
    struct Location
    {
        int xPos;
        int yPos;
    };
    // Khang added comment
    // Josh added comment
    Location location; // instantiate an inner object from struct location
    

    
public:
    /* Constructor*/
    Character(string Name, int row, int col, Dungeon& dungeon) : name(Name), dungeon(&dungeon)
    {
        // still need to implement math for determining base stats for each subclass
        setXPos(row-1);
        setYPos(rand() % col);
        cout << "X: " << location.xPos << " Y: " << location.yPos << endl;
        // dungeon->getRoom(x, y) will return a pointer to the room at row x, column y of the 2D array
        currentRoom = &(this->dungeon->getRoom(location.xPos, location.yPos));
        
         setInitialAttributes();
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
    
    // void pickupItem(items item);
    // void dropItem(items item)
    // void useItem(items item);
    // virtual void swapEquipment(equipments equipment) = 0;

    
    /* Interactions with Monsters */
    // void attack(monsters monster) = 0;
    void useSpecialAbility();
    void attack();
    bool accurateHit();
    
    /* Ineraction with RoomObjects */
    void readBook() const;
    void readMap() const;
    void useFlare() const
    void activateEndgameTreasure() const;

    
    /* Moving */
    void moveNorth();
    void moveSouth();
    void moveEast();
    void moveWest();
};



#endif /* Character_hpp */








