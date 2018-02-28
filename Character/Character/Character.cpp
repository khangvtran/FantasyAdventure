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
// DRAGON HEALTH : 50
// TITAN HEALTH : 40
// DRAGON BOSS HEALTH : 80




/* Constructor */
Character::Character(string Name, int row, int col, Dungeon& dungeon) : name(Name), dungeon(&dungeon), location(row, col)
{
    health = 100;
    lives = 3;
    setXPos(row-1);
    setYPos(rand() % col-1);
    cout << "Character constructor call (Initial Pos) \tX: " << location.xPos << " Y: " << location.yPos << endl;
    // dungeon->getRoom(x, y) will return a pointer to the room at row x, column y of the 2D array
    currentRoom = &(this->dungeon->getRoom(location.xPos, location.yPos));
    
    Item* item = new IronHelmet(); // debug
    itemList.insertStart(item); // debug
    
    setInitialAttributes();
    cout << currentRoom->getDescription() << endl << endl;
}

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
            cerr << "You can only allocate a maximum of " << totalBaseStat << " points!" << endl;
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
            cerr << "You can only allocate a maximum of " << totalBaseStat << " points!" << endl;
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
    cout << "YOU DIED" << endl;
    lives--;
    if(lives < 0)
        alive = false;
    else
    {
        health = 100; // ALSO NEED TO IMPLEMENT EXTRA HEALTH BASED ON EQUIPMENT
        cout << "You have " << lives << " lives remaining." << endl;
    }
}

void Character::setXPos(int X)
{
    if(X >= 0 && X < location.xBound)
        location.xPos = X;
}


void Character::setYPos(int Y)
{
    if(Y >= 0 && Y < location.yBound)
        location.yPos = Y;
}


/* Other operations */



 /* Interaction with Items - Equipment */
void Character::pickupItem(string item)
{
    cout << "pickupItem isn't implemented yet" << endl;
}

void Character::dropItem(string item)
{
    int index = itemList.linearSearch(item);
    if(index != -1)
    {
        itemList.advanceToIndex(index);
        currentRoom->setItem(itemList.getIterator());
        //currentRoom->removeItem(item);
        itemList.removeIterator();
        cout << "ITEM REMOVED from inventory" << endl; // debugging
    }
    else
        cout << "COULDN'T FIND " << item << " in inventory!" << endl;
}

void Character::useItem(string item)
{
    cout << "useItem isn't implemented yet" << endl;
}


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
        cout << "DIRECT HIT!" << endl;
        cout << "MONSTER HEALTH before: " << m->getHealth(); // debug
        double damage = strength * 1.5;
        m->modifyHealth(damage);
        cout << "MONSTER HEALTH after: " << m->getHealth(); // debug
    }
    bool flag = false; // THIS IS NEW
    cout << "Health before attack: " << health << endl; // debug
    double monsterDamage = m->attack(luck, flag);
    setHealth(health - monsterDamage);
    
    cout << "Health after attack: " << health << endl; // debug
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







/* Interactions with RoomObjects*/

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
            dungeon->printMap(location.xPos, location.yPos);
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
        Flare* FlarePtr = dynamic_cast<Flare*>(currentRoomObjectPtr);
        if (FlarePtr)
        {
            FlarePtr->DisplayAdjacentRoomObject();                     // from RoomObject
            dungeon->printAdjacentRooms(location.xPos, location.yPos); // from dungeon
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

void Character::activateEndgameTreasure() const
{
    RoomObject* currentRoomObjectPtr = currentRoom->getRoomObjectPtr();
    if (currentRoomObjectPtr)   // there is a room object in the room
    {
        Treasure* TreasurePtr = dynamic_cast<Treasure*>(currentRoomObjectPtr);
        if (TreasurePtr)       // check if the Room Object is a Treasure
        {
            // check is monster is alive?
            // Room -> monster in the room -> ???
            //  cout << "You hav to kill monster first",
            // OR
            // check item if three gems are there.
            //if not (itemList.search(ruby) && itemList.search(sapphire) && itemList.search(emmerald))
            // cout << "You habe to collect the three gem" << endl;
            
            TreasurePtr->DisplayWinGameMess();
        }
        else
        {
            cout << "This is not a treasure. Gosh, how can you get this far being so dumb!" << endl;
        }
    }
    else
    {
        cout << "Ain't no nothing lying around. Get your eyes checked! " << endl;
    }
}

void Character::move(string direction) throw(const char*)
{
    try {
        if(direction == "north")
            _moveNorth();
        else if(direction == "south")
            _moveSouth();
        else if(direction == "west")
            _moveWest();
        else if(direction == "east")
            _moveEast();
        else
            throw string("Invalid move direction: " +direction).c_str();
    } catch (const char*) {
        throw;
    }
    cout << currentRoom->getDescription() << endl << endl;
}

void Character::_moveNorth() throw(const char*)
{
    if(currentRoom->checkNorth())
    {
        setYPos(location.yPos-1);
        currentRoom = &(dungeon->getRoom(location.xPos, location.yPos));
    }
    else // exception, handled by main
        throw "There's a wall in the North direction!";
}

void Character::_moveSouth() throw(const char*)
{
    if(currentRoom->checkSouth())
    {
        setYPos(location.yPos+1);
        currentRoom = &(dungeon->getRoom(location.xPos, location.yPos));
    }
    else // exception, handled by main
        throw "There's a wall in the South direction!";;
}

void Character::_moveEast() throw(const char*)
{
    if(currentRoom->checkEast())
    {
        setXPos(location.xPos+1);
        currentRoom = &(dungeon->getRoom(location.xPos, location.yPos));
    }
    else // exception, handled by main
        throw "There's a wall in the East direction!";
}

void Character::_moveWest() throw(const char*)
{
    if(currentRoom->checkWest())
    {
        setXPos(location.xPos-1);
        currentRoom = &(dungeon->getRoom(location.xPos, location.yPos));
    }
    else // exception, handled by main
        throw "There's a wall in the West direction!";
}


