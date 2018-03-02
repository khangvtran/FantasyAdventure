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
#include <sstream>
#include "Generation.h"

// DRAGON HEALTH : 50
// TITAN HEALTH : 40
// DRAGON BOSS HEALTH : 80




/* Constructor */
Character::Character(string Name, int row, int col, Dungeon& dungeon) : name(Name), dungeon(&dungeon), location(row, col)
{
    equipmentSet = {{"Helmet", new IronHelmet},
                    {"Armor", new IronArmor},
                    {"Greaves", new IronGreaves}};
    
    
    health = maxHealth = 100 + equipmentHealth();
    
    cout << "health is : " << health << endl;
    lives = 3;
    setRowPos(rand() % row-1);
    setColPos(rand() % col-1);
    cout << "Character constructor call (Initial Pos) \tX: " << location.row << " Y: " << location.col << endl;
    // dungeon->getRoom(x, y) will return a pointer to the room at row y, column x of the 2D array
    currentRoom = &(this->dungeon->getRoom(location.row, location.col));
    
    
    

    Item* item = new MithrilArmor(); // debug
    itemList.insertStart(item); // debug
    item = new HealthPotion;
    itemList.insertStart(item);
    setInitialAttributes();
    cout << currentRoom->getDescription() << endl << endl;
}

/* Accessor */

string Character::getName() const
{
    return name;
}
int Character::getMaxHealth() const
{
    return maxHealth;
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

int Character::getColPos() const
{
    return location.col;
}

int Character::getRowPos() const
{
    return location.row;
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
    if(health <= maxHealth)
        health = Health;
    if(health < 0)
        _die();
}
void Character::setMaxHealth(int MaxHealth)
{
    maxHealth = MaxHealth;
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

void Character::_die()
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

void Character::setColPos(int X)
{
    if(X >= 0 && X < location.xBound)
        location.col = X;
}

void Character::setRowPos(int Y)
{
    if(Y >= 0 && Y < location.yBound)
        location.row = Y;
}


/* Other operations */



 /* Interaction with Items - Equipment */
void Character::pickupItem(string item)
{
    if (currentRoom->contains(item))                    // check if there is an item
    {
        Item* newItem = currentRoom->removeItem(item);  // take the item from the room
        
        Equipment* newEquipment = dynamic_cast<Equipment*>(newItem); // downcast into equipment
        
        if (! newEquipment) // if this is consumable item, do insert
        {
            itemList.insertStart(newItem);
            cout << "Picked up " << item << ". It's now in your inventory" << endl;
            return;
        }
        else               // if this is equipment, do swap
        {
            Helmet* helmet = dynamic_cast<Helmet*>(newEquipment);
            if(helmet)
            {
                dropItem("Helmet");
                equipmentSet["Helmet"] = helmet;
                cout << "You picked up " << helmet->name() << "and put it on!" << endl;
                return;
            }
            Armor* armor = dynamic_cast<Armor*>(newEquipment);
            if(armor)
            {
                dropItem("Armor");
                equipmentSet["Armor"] = armor;
                cout << "You picked up " << armor->name() << "and put it on!" << endl;
                return;
            }
            
            Greaves* greaves = dynamic_cast<Greaves*>(newEquipment);
            if(greaves)
            {
                dropItem("Hreaves");
                equipmentSet["Greaves"] = greaves;
                cout << "You picked up " << greaves->name() << "and put it on!" << endl;
                return;
            }
        }
    }
    else
    {
        cout << "No items in the room, friends!" << endl;
    }

}

void Character::dropItem(string item)
{
    if(item == "Armor")
    {
        currentRoom->setItem(equipmentSet["Armor"]);
        equipmentSet["Armor"] = nullptr;
    }
    else if(item == "Helmet")
    {
        currentRoom->setItem(equipmentSet["Helmet"]);
        equipmentSet["Helmet"] = nullptr;
    }
    else if(item == "Greaves")
    {
        currentRoom->setItem(equipmentSet["Greaves"]);
        equipmentSet["Greaves"] = nullptr;
    }
    else
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
}


void Character::useItem(string item)
{
    cout << "useItem isn't implemented yet" << endl;
    
    // check if item in inventory,
    int index = itemList.linearSearch(item);
    if (index != -1)
    {
        if (item == "Health Potion")
        {
            cout << "Use Health Potion" << endl;
        }
        else if (item == "Max Health Potion")
        {
            cout << "use Max Health Potion" << endl;
        }
        else if (item == "Strength Potion")
        {
            cout << "Use Max Health Potion" << endl;
        }
        else if (item == "Strength Potion")
        {
            cout << "Use Strength Potion" << endl;
        }
        else if (item == "Luck Potion")
        {
            cout << "use Luck Potion" << endl;
        }
        else if (item == "Int Potion")
        {
            cout << "Use Int Potion" << endl;
        }
    }
    else
    {
        cout << "You don't have that item, pal!" << endl;
    }
    

    
}

int Character::equipmentHealth()
{
    int sum = 0;
    if(equipmentSet["Helmet"] != nullptr)
        sum += equipmentSet["Helmet"]->getvalue();
    
    if(equipmentSet["Armor"] != nullptr)
        sum+=equipmentSet["Armor"]->getvalue();
    
    if(equipmentSet["Greaves"] != nullptr)
        sum+=equipmentSet["Greaves"]->getvalue();
    
    return sum;
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
    if( m!= nullptr)
        
    if(_HitOrHeal())
    {
        cout << "DIRECT HIT!" << endl;
        cout << "MONSTER HEALTH before: " << m->getHealth(); // debug
        double damage = strength * 1.5;
        m->modifyHealth(damage); // modify health COULD return a true/false to indicate monster is alive or dead, then we can call ROOM's REMOVE on monster to set to nullptr
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
bool Character::_HitOrHeal() const // CHANGE: AccuracyHit() changed into HitOrHeal()
{
    double accuracyRange = pow(luck, log10(100)/log10(18/* "MAX LUCK"*/));
    return (rand()%100 <= accuracyRange);
}



/* Interactions with RoomObjects*/

void Character::_readBook() const
{
    RoomObject* currentRoomObjectPtr = currentRoom->getRoomObjectPtr();
    if (currentRoomObjectPtr)
    {
        Book* BookPtr = dynamic_cast<Book*>(currentRoomObjectPtr);
        if (BookPtr)
        {
            BookPtr->use();
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


void Character::_readMap() const
{
    RoomObject* currentRoomObjectPtr = currentRoom->getRoomObjectPtr();
    if (currentRoomObjectPtr)
    {
        Map* MapPtr = dynamic_cast<Map*>(currentRoomObjectPtr);
        if (MapPtr)
        {
            MapPtr->use();
            dungeon->printMap(location.row, location.col);
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



void Character::_useFlare() const
{
    RoomObject* currentRoomObjectPtr = currentRoom->getRoomObjectPtr();
    if (currentRoomObjectPtr)
    {
        Flare* FlarePtr = dynamic_cast<Flare*>(currentRoomObjectPtr);
        if (FlarePtr)
        {
            FlarePtr->use();                     // from RoomObject
            dungeon->printAdjacentRooms(location.row, location.col); // from dungeon
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


void Character::_drinkFromFountain()
{
    RoomObject* currentRoomObjectPtr = currentRoom->getRoomObjectPtr();
    if (currentRoomObjectPtr)
    {
        Fountain* FoutainPtr = dynamic_cast<Fountain*>(currentRoomObjectPtr);
        if (FoutainPtr)
        {
            if (_HitOrHeal())
            {
                cout << "You were lucky this time! Your health increased from " << getHealth() << " to ";
                setHealth(getHealth() + 3 * getIntelligence());
                cout << getHealth() << "." << endl << endl;
            }
            else
            {
                cout << "Ouch! That water might have been slightly poisonous. Lost 10 health." << endl << endl;
                setHealth(getHealth()-10);
            }
        }
        else
        {
            cout << "How can you possibly mistake this object for a foutain, fool!" << endl;
        }
    }
    else
    {
        cout << "Do you see anything around. I don't" << endl;
    }
}




void Character::_activateEndgameTreasure() const        // CHANGE: complete
{
    RoomObject* currentRoomObjectPtr = currentRoom->getRoomObjectPtr();
    if (currentRoomObjectPtr)   // there is a room object in the room
    {
        Treasure* TreasurePtr = dynamic_cast<Treasure*>(currentRoomObjectPtr);
        if (TreasurePtr)       // check if the Room Object is a Treasure
        {
            // check if boss is dead
            if (currentRoom->getMonsterPtr()->isAlive())
            {
                cout << "May be it just me but do you see that colossal monster guarding the treasure there, mate????" << endl;
                return;
            }
            // check if all gems are in itemList
            if (itemList.linearSearch("Ruby") == -1 || itemList.linearSearch("Saphhire") == -1 || itemList.linearSearch("Emmerald") == -1)
            {
                cout << "You still have to acquire all three gems: Ruby, Sapphire, and Emmerald" << endl;
                return;
            }
            
            TreasurePtr->use();   // display winning message. Game keeps going on.
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





/* Navigating */

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
        setRowPos(location.row-1);
        currentRoom = &(dungeon->getRoom(location.row, location.col));
    }
    else // exception, handled by main
        throw "There's a wall in the North direction!";
}

void Character::_moveSouth() throw(const char*)
{
    if(currentRoom->checkSouth())
    {
        setRowPos(location.row+1);
        currentRoom = &(dungeon->getRoom(location.row, location.col));
    }
    else // exception, handled by main
        throw "There's a wall in the South direction!";;
}

void Character::_moveEast() throw(const char*)
{
    if(currentRoom->checkEast())
    {
        setColPos(location.col+1);
        currentRoom = &(dungeon->getRoom(location.row, location.col));
    }
    else // exception, handled by main
        throw "There's a wall in the East direction!";
}

void Character::_moveWest() throw(const char*)
{
    if(currentRoom->checkWest())
    {
        setColPos(location.col-1);
        currentRoom = &(dungeon->getRoom(location.row, location.col));
    }
    else // exception, handled by main
        throw "There's a wall in the West direction!";
}

void Character::activate(string thing)
{
    if(thing == "map")
        _readMap();
    else if(thing == "book")
        _readBook();
    else if(thing == "fountain")
        _drinkFromFountain();
    else if(thing == "treasure")
        _activateEndgameTreasure();
    else if(thing == "flare")
        _useFlare();
}


void Character::cheat(string cmd, string cmd2)
{
    if(cmd == "god")
    {
        setMaxHealth(15000);
        setHealth(15000);
        setStrength(90);
        setIntelligence(90);
        setLuck(90);
        cout << "God mode activated. You suck." << endl;
        return;
    }
    else if(cmd == "tp")
    {
        cout << "here" << endl;
        std::istringstream is(cmd2);
        int row,col;
        is >> row >> col;
        setRowPos(row);
        setColPos(col);
        cout << "Teleported to (" << row << "," << col << ")." << endl;
        currentRoom = &(this->dungeon->getRoom(location.row, location.col));
        cout << currentRoom->getDescription() << endl << endl;
    }
    else if(cmd == "spawn")
    {
        Generation spawner;
        Item* thing = spawner.generateItem(spawner.itemContainer[cmd2]);
        currentRoom->setItem(thing);
        pickupItem(thing->name());
    }
}
