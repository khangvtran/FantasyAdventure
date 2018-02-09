//
//  Character.cpp
//  Character
//
//  Created by Khang Tran on 2/2/18.
//  Copyright © 2018 Khang Tran and Joshua Kuan. All rights reserved.
//

#include "Character.h"

/* Accessor */

string Character::getName() const
{
    return name;
}

int Character::getHealth() const
{
    return health;
}

int Character::getStrength() const
{
    return strength;
}

int Character::getIntelligence() const
{
    return intelligence;
}

int Character::getLuck() const
{
    return luck;
}

bool Character::isAlive() const
{
    return alive;
}

int Character::getXPos() const
{
    return location.xPos;
}

int Character::getYPos() const
{
    return location.yPos;
}



/* Manipulator */
void Character::setName(string Name)
{
    name = Name;
}

void Character::setHealth(int Health)
{
    health = Health;
}

void Character::setStrength(int Strength)
{
    strength = Strength;
}


void Character::setIntelligence(int Intelligence)
{
    intelligence = Intelligence;
}

void Character::setLuck(int Luck)
{
    luck = Luck;
}

void Character::die()
{
    alive = false;
}

void Character::setXPos(int X)
{
    location.xPos = X;
}


void Character::setYPos(int Y)
{
    location.yPos = Y;
}


/* Other operations */

/*
void Character::pickupItem(items item)
{
    
}
*/



/*
 void character::dropItem(items item)
 {
 
 }
 */



/*
 void Character::useItem(items item)
 {
 
 }
 
 */


/*void move (char* moveCommand)
{
    cout << "Calling move Command" << endl;
    // Ask Anna about the map
}*/

void Character::moveNorth()
{
    
}

void Character::moveSouth()
{
    
}

void Character::moveEast()
{
    
}

void Character::moveWest()
{
    
}











