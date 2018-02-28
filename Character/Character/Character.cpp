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

void Character::setInitialAttributes()
{
    int temp = -1;
    int totalBaseStat = 18;
    cout << "You have " << totalBaseStat << " points to allocate into Strength (affecting damage), Intelligence (affecting healing), and Luck (affecting accuracy)" << endl << endl;
    do
    {
        cout << "Points remaining: " << totalBaseStat << endl;
        cout << "Enter number of points to allocate for strength: ";
        cin >> temp;
        if(temp < 0 || temp > totalBaseStat)
            cerr << " ERROR" << endl;
        else
        {
            setStrength(temp);
            totalBaseStat -= temp;
            break;
        }
    } while(temp < 0 || totalBaseStat > 0);
    cout << "You allocated " << strength << " points into strength" << endl << endl;
    
    while (temp < 0 || totalBaseStat > 0)
    {
        cout << "Points remaining: " << totalBaseStat << endl;
        cout << "Enter number of points to allocate for intelligence: ";
        cin >> temp;
        if(temp < 0 || temp > totalBaseStat)
            cerr << " ERROR" << endl;
        else
        {
            setIntelligence(temp);
            totalBaseStat -= temp;
            break;
        }
    }
    cout << "You allocated " << intelligence << " points to intelligence" << endl << endl;
    setLuck(totalBaseStat); // sets remaining
    cout << luck << " points were automatically allocated into luck" << endl << endl;
    
    cin.ignore(10, '\n');
}


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
    bool flag = false; // THIS IS NEW
    
    double monsterDamage = m->attack(luck, flag);
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






void Character::readBook() const
{
    RoomObject* currentRoomObjectPtr = currentRoom->getRoomObjectPtr();
    if (currentRoomObjectPtr)
    {
        Book* BookPtr = dynamic_cast<Book*>(currentRoomObjectPtr);
        if (BookPtr)
        {
            BookPtr->read();
        }
        else
        {
            cout << "Does this thing look like a book to you, mate?" << endl;
        }
    }
    else
    {
        cout << "Do you see anything around, fool?" << endl;
    }
}






void Character::readMap() const
{
    RoomObject* currentRoomObjectPtr = currentRoom->getRoomObjectPtr();
    if (currentRoomObjectPtr)
    {
        Map* MapPtr = dynamic_cast<Map*>(currentRoomObjectPtr);
        if (MapPtr)
        {
            MapPtr->check();
        }
        else
        {
            cout << "This is not a map. Are you high, mate" << endl;
        }
    }
    else
    {
        cout << "The room is empty, pal." << endl;
    }
}



void Character::useFlare() const
{
    RoomObject* currentRoomObjectPtr = currentRoom->getRoomObjectPtr();
    if (currentRoomObjectPtr)
    {
        Flares* FlarePtr = dynamic_cast<Flares*>(currentRoomObjectPtr);
        if (FlarePtr)
        {
            FlarePtr->DisplayAdjacentRoomObject();
        }
        else
        {
            cout << "This is not a flare. You are a fool, aren't you" << endl;
        }
    }
    else
    {
        cout << "Do you see anything around. I don't" << endl;
    }
}




void Character::moveNorth() // throw(exception)
{
    if(currentRoom->checkNorth())    // Anna: Room class needs checkNorth()
    {
        location.yPos--;
        currentRoom = &(dungeon->getRoom(location.xPos, location.yPos));    //Anna: dungeon class needs getRoom(x, y)
        cout << currentRoom->getDescription();
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
        currentRoom = &(dungeon->getRoom(location.xPos, location.yPos));    //Anna: dungeon class needs getRoom(x, y)
        cout << currentRoom->getDescription();
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
        currentRoom = &(dungeon->getRoom(location.xPos, location.yPos));    //Anna: dungeon class needs getRoom(x, y)
        cout << currentRoom->getDescription();
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
        currentRoom = &(dungeon->getRoom(location.xPos, location.yPos));    //Anna: dungeon class needs getRoom(x, y)
        cout << currentRoom->getDescription();
    }
    else
    {
        // exception, handled by main
        // throw exception("Player cannot move West)"
    }
}













