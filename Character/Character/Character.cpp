//
//  Character.cpp
//  Character
//
//  Created by Khang Tran on 2/2/18.
//  Copyright © 2018 Khang Tran and Joshua Kuan. All rights reserved.
//

#include "Character.h"
#include <cstdlib>
#include <cmath>
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
    if(health < 0)
        die();
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

/**
 Interaction between character and monster in the room
 Precondition: There is a monster alive in the room AND character is not dead
 calls accurateHit() to check the possibility (T/F) of character hitting the monster
 
 Damage formula: strength * 1.5
 
 calls monster's attack() function and subtracts character health
 subtracts monter's health based on calculated damage
 
*/
void Character::attack()
{
    // have to implement if room does not have monster
    // throw exception?
    
    Monster* m = currentRoom->getMonsterPtr();
    if(accurateHit())
    {
        double damage = strength * 1.5;
        m->setHealth(m->getHealth() - damage);
    }
    double monsterDamage = m->attack();
    setHealth(health - monsterDamage);
    if(!isAlive())
        ;//throw exception (died);
}

/**
 Calculates an accuracy range based on character's luck (MAX LUCK = 18, ACCURACY == 100%, Total initial Atrributes = 18)
 Returns true if character's attack will NOT miss
 Returns false if character's attack WILL miss
 */
bool Character::accurateHit()
{
    double accuracyRange = pow(luck, log10(100)/log10(18/* "MAX LUCK"*/));
    return (rand()%100 <= accuracyRange);
}


void Character::moveNorth() // throw(exception)
{
    if(currentRoom->checkNorth())    // Anna: Room class needs checkNorth()
    {
        location.yPos--;
        currentRoom = dungeon->getRoom(location.xPos, location.yPos);    //Anna: dungeon class needs getRoom(x, y)
        currentRoom->print();
    }
    else
    {
        // exception, handled by main
        // throw exception("Player cannot move north)"
    }
}

void Character::moveSouth() // throw(exception)
{
    if(currentRoom->checkSouth())    // Anna: Room class needs checkNorth()
    {
        location.yPos++;
        currentRoom = dungeon->getRoom(location.xPos, location.yPos);    //Anna: dungeon class needs getRoom(x, y)
        currentRoom->print();
    }
    else
    {
        // exception, handled by main
        // throw exception("Player cannot move South)"
    }
}

void Character::moveEast() // throw(exception)
{
    if(currentRoom->checkEast())    // Anna: Room class needs checkNorth()
    {
        location.xPos++;
        currentRoom = dungeon->getRoom(location.xPos, location.yPos);    //Anna: dungeon class needs getRoom(x, y)
        currentRoom->print();
    }
    else
    {
        // exception, handled by main
        // throw exception("Player cannot move East)"
    }
}

void Character::moveWest() // throw(exception)
{
    if(currentRoom->checkWest())    // Anna: Room class needs checkNorth()
    {
        location.xPos--;
        currentRoom = dungeon->getRoom(location.xPos, location.yPos);    //Anna: dungeon class needs getRoom(x, y)
        currentRoom->print();
    }
    else
    {
        // exception, handled by main
        // throw exception("Player cannot move West)"
    }
}












