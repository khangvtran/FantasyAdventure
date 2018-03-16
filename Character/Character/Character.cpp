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
#include <iomanip>
#include "Generation.h"

/* Constructor */
Character::Character(const std::string& Name, const int& row, const int& col, Dungeon& dungeon) : name(Name), dungeon(&dungeon), strength(0), intelligence(0), luck(0), alive(true), lives(3)
{
    
    
    location = new Location(row, col);
    setRowPos(rand() % (row - 5) + 5); // spawns player at row (5-9)
    setColPos(rand() % col); // spawns player anywhere at col (0-9)
    currentRoom = &(this->dungeon->getRoom(location->row, location->col));
    
    equipmentSet = {{"helmet", new IronHelmet},
                    {"armor", new IronArmor},
                    {"greaves", new IronGreaves},
                    {"weapon", nullptr}
    };
    
    maxHealth = 100 + _equipmentHealth(); // sets health and maxhealth to 100 + sum equipment health (100 + 6+5+4)
    health = maxHealth;
    


    setInitialAttributes(24);
    
    if(_randomizer())
        equipmentSet["weapon"] = new IronSword;
    else
        equipmentSet["weapon"] = new IronDagger;
    

    std::cout << *currentRoom;
}


/* Destructor */
Character::~Character()
{
    // Linkedlist has destructor

    // deallocate equipment
    if(equipmentSet["helmet"] != nullptr)
    {
        delete equipmentSet["helmet"];
        equipmentSet["helmet"] = nullptr;
    }
    if(equipmentSet["armor"] != nullptr)
    {
        delete equipmentSet["armor"];
        equipmentSet["armor"] = nullptr;
    }
    if(equipmentSet["greaves"] != nullptr)
    {
        delete equipmentSet["greaves"];
        equipmentSet["greaves"] = nullptr;
    }
    if(equipmentSet["weapon"] != nullptr)
    {
        delete equipmentSet["weapon"];
        equipmentSet["weapon"] = nullptr;
    }

    // deallocate location struct
    delete location;
}

void Character::_activateEndgameTreasure() const throw(AdventureErrors::MissingObject, AdventureErrors::CharacterDeath)       // CHANGE: complete
{
    RoomObject* roomObjPtr = currentRoom->getRoomObjectPtr();
    if (!roomObjPtr)   // there is a room object in the room
        throw AdventureErrors::MissingObject("Ain't nothing lying around. Get your eyes checked! ");

    Treasure* treasure = dynamic_cast<Treasure*>(roomObjPtr);
    if (treasure)       // check if the Room Object is a Treasure
    {
        // check if boss is dead
        if (currentRoom->getMonsterPtr() != nullptr)
        {
            std::cout << "Maybe it's just me but do you see that colossal monster guarding the treasure there, mate??" << std::endl;
            return;
        }
        // check if all gems are in itemList
        if (inventory.linearSearch("ruby") == -1 || inventory.linearSearch("sapphire") == -1 || inventory.linearSearch("emerald") == -1)
        {
            std::cout << "You still have to acquire all three gems: ruby, sapphire, and emerald" << std::endl;
            return;
        }
        treasure->use();   // display winning message. Game ends here.
        throw AdventureErrors::CharacterDeath("");
    }
    else
        throw AdventureErrors::MissingObject("This is not a treasure. Gosh, how did you get this far by being so dumb!");
}


void Character::_die()
{
    std::cout << std::endl << std::endl << "***** YOU DIED *****" << std::endl << std::endl;
    std::cout << "What a shame.. Should've tried harder than that!" << std::endl;
    lives--;
    if(lives < 0)
    {
        alive = false;
        return;
    }
    else
    {
        health = maxHealth; // ALSO NEED TO IMPLEMENT EXTRA HEALTH BASED ON EQUIPMENT
        if(lives == 0)
            std::cout << "You're on your last life! What are you doing‽" << std::endl;
        else
        {
            std::cout << "Luckily, you seem to have " << lives;
            if(lives > 1)
                std::cout << " lives";
            else
                std::cout  << " life";
             std::cout << " remaining." << std::endl;
        }
    }
}

void Character::_drinkFromFountain() throw(AdventureErrors::MissingObject)
{
    RoomObject* roomObjPtr = currentRoom->getRoomObjectPtr();
    if (!roomObjPtr)
        throw AdventureErrors::MissingObject("Do you see anything around. I don't");

    Fountain* fountain = dynamic_cast<Fountain*>(roomObjPtr);
    if (fountain)
    {
        fountain->use();
        if (_randomizer())
        {

            if(((health + 3 * intelligence) > health) && (health < maxHealth))
            {
                std::cout << "You were lucky this time! Your health increased from " << health;
                setHealth(health + 3 * intelligence);
                std::cout << " to " << health << "." << std::endl << std::endl;
            }
            else
                std::cout << "The fountain would've healed you... but you were already at full health.";
        }
        else
        {
            std::cout << "Ouch! That water might have been slightly poisonous. You lost 10 health." << std::endl;
            std::cout << "Your health decreased from " << health << " to " << health - 10 << "." << std::endl;
            setHealth(health - 10);
        }
    }
    else
        throw AdventureErrors::MissingObject("How can you possibly mistake this object for a foutain, fool!");
}


void Character::_moveEast() throw(AdventureErrors::InvalidMove)
{
    if(currentRoom->checkEast())
    {
        setColPos(location->col + 1);
        currentRoom = &(dungeon->getRoom(location->row, location->col));
    }
    else // exception, handled by main
        throw AdventureErrors::InvalidMove("There's a wall in the East direction!");
}

void Character::_moveNorth() throw(AdventureErrors::InvalidMove)
{
    if(currentRoom->checkNorth())
    {
        setRowPos(location->row - 1);
        currentRoom = &(dungeon->getRoom(location->row, location->col));
    }
    else // exception, handled by main
        throw AdventureErrors::InvalidMove("There's a wall in the North direction!");
}

void Character::_moveSouth() throw(AdventureErrors::InvalidMove)
{
    if(currentRoom->checkSouth())
    {
        setRowPos(location->row + 1);
        currentRoom = &(dungeon->getRoom(location->row, location->col));
    }
    else // exception, handled by main
        throw AdventureErrors::InvalidMove("There's a wall in the South direction!");
}

void Character::_moveWest() throw(AdventureErrors::InvalidMove)
{
    if(currentRoom->checkWest())
    {
        setColPos(location->col - 1);
        currentRoom = &(dungeon->getRoom(location->row, location->col));
    }
    else // exception, handled by main
        throw AdventureErrors::InvalidMove("There's a wall in the West direction!");
}




void Character::_printAttributes() const
{
    std::cout << "Character Attributes: " << std::endl;
    std::cout << "Lives remaining: " << lives << std::endl;
    std::cout << "Health: " << health << std::endl;
    std::cout << "Max Health: " << maxHealth << std::endl;
    std::cout << "Strength: " << strength << std::endl;
    std::cout << "Intelligence: " << intelligence << std::endl;
    std::cout << "Luck: " << luck << std::endl;
    std::cout << std::endl;
}

void Character::_printEquipmentSet() const
{
    if(equipmentSet.size() > 0)
        std::cout << "Character Equipment: " << std::endl;
    try
    {
        if(equipmentSet.at("helmet")!= nullptr)
            std::cout << equipmentSet.at("helmet")->name() << " (+" << equipmentSet.at("helmet")->getValue() << " max health)"<< std::endl;
        if(equipmentSet.at("armor")!= nullptr)
            std::cout << equipmentSet.at("armor")->name() << " (+" << equipmentSet.at("armor")->getValue() << " max health)"<< std::endl;
        if(equipmentSet.at("greaves")!= nullptr)
            std::cout << equipmentSet.at("greaves")->name() << " (+" << equipmentSet.at("greaves")->getValue() << " max health)"<< std::endl;
        if(equipmentSet.at("weapon")!= nullptr)
            std::cout << std::setprecision(2) << equipmentSet.at("weapon")->name() << " (+" << equipmentSet.at("weapon")->getValue() << " damage)";
        if(equipmentSet.at("weapon")!= nullptr && dynamic_cast<Dagger*>(equipmentSet.at("weapon")) != nullptr)
            std::cout << " [Chance to do critical hit! (x2)]";

    } catch (std::out_of_range &err)
    {
        std::cerr << err.what() << std::endl;
    }

}

void Character::_printInventory() const
{
    if(!inventory.isEmpty())
    {
        std::cout << "Character Inventory: " << std::endl;
        inventory.printNumberedList();
        std::cout << std::endl;
    }
}

/**
 Calculates an accuracy range based on character's luck (MAX LUCK = 18, ACCURACY == 100%, Total initial Atrributes = 18)
 Returns true if character's attack will NOT miss
 Returns false if character's attack WILL miss
 */
bool Character::_randomizer() const // CHANGE: AccuracyHit() changed into HitOrHeal()
{
    double accuracyRange = pow(luck, log10(100) / log10(16));
    return (rand() % 100 <= accuracyRange);
}

void Character::_readBook() const throw(AdventureErrors::MissingObject)
{
    RoomObject* roomObjPtr = currentRoom->getRoomObjectPtr();
    if(!roomObjPtr)
        throw AdventureErrors::MissingObject("Do you see a book lying around, fool?");

    Book* book = dynamic_cast<Book*>(roomObjPtr);
    if(book)
        book->use();
    else
        throw AdventureErrors::MissingObject("Does this thing look like a book to you, mate?");
}

void Character::_readMap() const throw(AdventureErrors::MissingObject)
{
    RoomObject* roomObjPtr = currentRoom->getRoomObjectPtr();
    if(!roomObjPtr)
        throw AdventureErrors::MissingObject("The room is empty, pal.");

    Map* map = dynamic_cast<Map*>(roomObjPtr);
    if(map)
    {
        std::string cmd = "";
        do
        {
            std::cout << std::endl << "Which map would you like to view? [basic, monster, roomobject, item, all]: ";
            std::cin >> cmd;
            if(cmd == "basic")
            {
                map->use();
                dungeon->printMap(location->row, location->col, Dungeon::BASIC);
            }
            else if(cmd == "monster")
            {
                map->use();
                dungeon->printMap(location->row, location->col, Dungeon::MONSTER);
            }
            else if(cmd == "roomobject")
            {
                map->use();
                dungeon->printMap(location->row, location->col, Dungeon::ROOMOBJECT);
            }
            else if(cmd == "item")
            {
                map->use();
                dungeon->printMap(location->row, location->col, Dungeon::ITEM);
            }
            else if(cmd == "all")
            {
                map->use();
                dungeon->printMap(location->row, location->col, Dungeon::ALL);
            }
            if(cmd == "basic" || cmd == "monster" || cmd == "roomobject" || cmd == "item" || cmd == "all") // fixed this
                break;
        } while(cmd != "basic" || cmd != "monster" || cmd != "roomobject" || cmd != "item" || cmd != "all"); // fixed this

        std::cin.ignore(10, '\n');
        std::cin.clear();
    }
    else
        throw AdventureErrors::MissingObject("This is not a map. Are you high, mate?");
}

void Character::_useFlare() const throw(AdventureErrors::MissingObject)
{
    RoomObject* roomObjPtr = currentRoom->getRoomObjectPtr();
    if(!roomObjPtr)
        throw AdventureErrors::MissingObject("Do you see anything around? I sure don't.");

    Flare* flare = dynamic_cast<Flare*>(roomObjPtr);
    if(flare)
    {
        flare->use();
        dungeon->printAdjacentRooms(location->row, location->col);
    }
    else
        throw AdventureErrors::MissingObject("This is not a flare. What are you, blind?");
}

void Character::_useKillScroll()
{
    Monster* m = currentRoom->getMonsterPtr();
    if(m == nullptr)
    {
        std::cout << "There is no monster. What are you using that kill scroll for, pal? " << std::endl;
        return;
    }
    else
    {
        m->modifyHealth(m->getHealth() + 1);    // kill the monster
        currentRoom->removeMonster();           // remove monster from the room
        std::cout << *currentRoom;
    }
}

/**
 Interaction between character and monster in the room
 Precondition: There is a monster alive in the room AND character is not dead
 calls accurateHit() to check the possibility (T/F) of character hitting the monster

 Damage formula: strength * 1.5

 calls monster's attack() function and subtracts character health
 subtracts monter's health based on calculated damage

*/
void Character::attack() throw(AdventureErrors::CharacterDeath)
{
    // have to implement if room does not have monster
    // throw exception?

    Monster* m = currentRoom->getMonsterPtr();
    if(m == nullptr)
    {
        std::cout << std::endl << "There's no monster in the room." << std::endl;
        return;
    }
    if(_randomizer())
    {
        double modifier = (equipmentSet["weapon"] != nullptr ? equipmentSet["weapon"]->getValue() : 1);
        double damage = 1.2 * strength + modifier;
        if(_randomizer() && dynamic_cast<Dagger*>(equipmentSet.at("weapon")) != nullptr)
        {
            std::cout << "Your dagger dealt double damage to " << m->getName() << "!" << std::endl;
            damage *= 2;
        }
        // put in miss std::cout
        std::cout << std::endl << "You dealt " << static_cast<int>(damage) << " damage to " << m->getName() << "." << std::endl;
        if(!m->modifyHealth(damage))
        {
            currentRoom->removeMonster(); // modify health COULD return a true/false to indicate monster is alive or dead, then we can call ROOM's REMOVE on monster to set to nullptr
            std::cout << *currentRoom; // ADDED
            return;
        }
    }
    else
        std::cout << std::endl << "You missed the " << m->getName() << " this time around!" << std::endl;
    double monsterDamage = m->attack(luck);
    if(monsterDamage != 0)
    {
        setHealth(health - monsterDamage);
        std::cout << "Your health is now: " << health << std::endl << std::endl;
    }
    else
        std::cout << std::endl << std::endl;

    if(!isAlive())
        throw AdventureErrors::CharacterDeath("You messed up. You definitely didn't win this time!"); //throw exception (died);

}


void Character::activate(const std::string& thing) throw(AdventureErrors::MissingObject, AdventureErrors::CharacterDeath)
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
    else
        std::cout << "You can't activate that!";
    std::cout << std::endl << std::endl;
}

void Character::cheat(const std::string& cmd, const std::string& cmd2)
{
    if(cmd == "god")
    {
        setMaxHealth(15000);
        setHealth(15000);
        setStrength(90);
        setIntelligence(90);
        setLuck(90);
        std::cout << "God mode activated. You suck." << std::endl;
        return;
    }
    else if(cmd == "tp")
    {
        std::istringstream is(cmd2);
        int row = 0, col = 0;
        is >> row >> col;
        setRowPos(row);
        setColPos(col);
        std::cout << "Teleported to (" << location->row << "," << location->col << ")." << std::endl;
        currentRoom = &(this->dungeon->getRoom(location->row, location->col));
        std::cout << *currentRoom;
    }
    else if(cmd == "spawn")
    {
        Generation spawner;
        try {
            Item* thing = spawner.generateItem(spawner.itemContainer.at(cmd2));
            currentRoom->setItem(thing);
            if(currentRoom->getMonsterPtr() != nullptr)
                std::cout << thing->name() << " was spawned on the ground. \nYou can't pick it up until you kill the " << currentRoom->getMonsterPtr()->getName() << " though." << std::endl << std::endl;
            else
                pickupItem(thing->name());
        } catch (std::out_of_range &err) {
            std::cerr << "Invalid type " << cmd2 << "." << std::endl << std::endl;
        }
    }
    else if(cmd == "map")
    {
        if(cmd2 == "basic")
            dungeon->printMap(location->row, location->col, Dungeon::BASIC);
        else if(cmd2 == "monster")
            dungeon->printMap(location->row, location->col, Dungeon::MONSTER);
        else if(cmd2 == "roomobject")
            dungeon->printMap(location->row, location->col, Dungeon::ROOMOBJECT);
        else if(cmd2 == "item")
            dungeon->printMap(location->row, location->col, Dungeon::ITEM);
        else if(cmd2 == "all")
            dungeon->printMap(location->row, location->col, Dungeon::ALL);
    }
}
void Character::dropItem(const std::string& item, bool fromPickup)
{
    size_t spacePos = item.find(" ");
    std::string secondWord = item.substr(spacePos + 1);
    if(secondWord == "armor")
    {
        Equipment* armor = equipmentSet["armor"];
        if(armor != nullptr)
        {
            if((health - armor->getValue()) <= 0)
            {
                std::cout << "Are you sure you want to drop that? Your health is dangerously low." << std::endl << std::endl;
                return;
            }
            if(item == armor->name() || fromPickup)
            {
                std::cout << "Dropped " << armor->name() << " on the ground." << std::endl << std::endl;
                setMaxHealth(maxHealth - armor->getValue());
                currentRoom->setItem(armor);
                equipmentSet["armor"] = nullptr;
                std::cout << *currentRoom;
                return;
            }
            else
                 std::cout << "You have to be more specific than that! Did you mean " << armor->name() << "?" << std::endl << std::endl;
        }
        else
            std::cout << "You got no armor to drop." << std::endl << std::endl;
    }
    else if(secondWord == "helmet")
    {
        Equipment* helmet = equipmentSet["helmet"];
        if(helmet != nullptr)
        {
            if((health - helmet->getValue()) <= 0)
            {
                std::cout << "Are you sure you want to drop that? Your health is dangerously low." << std::endl << std::endl;
                return;
            }
            if(item == helmet->name() || fromPickup)
            {
                std::cout << "Dropped " << helmet->name() << " on the ground." << std::endl << std::endl;
                setMaxHealth(maxHealth - helmet->getValue());
                currentRoom->setItem(helmet);
                equipmentSet["helmet"] = nullptr;
                std::cout << *currentRoom;
                return;
            }
            else
                 std::cout << "You have to be more specific than that! Did you mean " << helmet->name() << "?" << std::endl << std::endl;
        }
        else
            std::cout << "You got no helmet to drop." << std::endl << std::endl;
    }
    else if(secondWord == "greaves")
    {
        Equipment* greaves = equipmentSet["greaves"];
        if(greaves != nullptr)
        {
            if((health - greaves->getValue()) <= 0)
            {
                std::cout << "Are you sure you want to drop that? Your health is dangerously low." << std::endl << std::endl;
                return;
            }
            if(item == greaves->name() || fromPickup)
            {
                std::cout << "Dropped " << greaves->name() << " on the ground." << std::endl << std::endl;
                setMaxHealth(maxHealth - greaves->getValue());
                currentRoom->setItem(greaves);
                equipmentSet["greaves"] = nullptr;
                std::cout << *currentRoom;
                return;
            }
            else
                std::cout << "You have to be more specific than that! Did you mean " << greaves->name() << "?" << std::endl << std::endl;
        }
        else
            std::cout << "You got no greaves to drop." << std::endl << std::endl;
    }
    else if(secondWord == "sword" || secondWord == "dagger")
    {
        Equipment* weapon = equipmentSet["weapon"];
        if(weapon != nullptr)
        {
            if(item == weapon->name() || fromPickup)
            {
                std::cout << "Dropped " << equipmentSet["weapon"]->name() << " on the ground." << std::endl << std::endl;
                currentRoom->setItem(equipmentSet["weapon"]);
                equipmentSet["weapon"] = nullptr;
                std::cout << *currentRoom;
                return;
            }
            else
                std::cout << "You have to be more specific than that! Did you mean " << weapon->name() << "?" << std::endl << std::endl;
        }
        else
            std::cout << "You got no weapon to drop." << std::endl << std::endl;
    }
    else
    {
        int index = inventory.linearSearch(item);
        if(index != -1)
        {
            inventory.advanceToIndex(index);
            currentRoom->setItem(inventory.getIterator());
            inventory.removeIterator();
            std::cout << "Removed " << item << " from inventory. It's on the ground now." << std::endl << std::endl; // debugging
            std::cout << *currentRoom;
        }
        else
            std::cout << "Are you really sure you have " << item << " in your inventory?" << std::endl;
    }
}


int Character::_equipmentHealth() const
{
    int sum = 0;
    try
    {
        if(equipmentSet.at("helmet") != nullptr)
            sum += equipmentSet.at("helmet")->getValue();

        if(equipmentSet.at("armor") != nullptr)
            sum += equipmentSet.at("armor")->getValue();

        if(equipmentSet.at("greaves") != nullptr)
            sum += equipmentSet.at("greaves")->getValue();
    } catch (std::out_of_range &err)
    {
        std::cerr << err.what() << std::endl;
    }
    return sum;
}

int Character::getColPos() const
{
    return location->col;
}
int Character::getHealth() const
{
    return health;
}
int Character::getIntelligence() const
{
    return intelligence;
}

int Character::getLuck() const
{
    return luck;
}
int Character::getMaxHealth() const
{
    return maxHealth;
}
std::string Character::getName() const
{
    return name;
}
int Character::getRowPos() const
{
    return location->row;
}
int Character::getStrength() const
{
    return strength;
}
bool Character::isAlive() const
{
    return alive;
}

/* Navigating */

void Character::move(const std::string& direction) throw(AdventureErrors::InvalidMove)
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
            throw AdventureErrors::InvalidMove(std::string("Invalid move direction: " + direction).c_str());
    } catch (AdventureErrors::InvalidMove) {
        throw;
    }
    std::cout << std::endl << std::endl;
    std::cout << *currentRoom;
}

 /* Interaction with Items - Equipment */
void Character::pickupItem(const std::string& item)
{
    if (currentRoom->getMonsterPtr() != nullptr)
    {
        std::cout << "Waste the guarding monster first. No pain no gain, pal." << std::endl << std::endl;
        return;
    }

    if (currentRoom->contains(item))                    // check if there is an item
    {
        Item* newItem = currentRoom->removeItem(item);  // take the item from the room

        Equipment* newEquipment = dynamic_cast<Equipment*>(newItem); // downcast into equipment

        if (!newEquipment) // if this is consumable item, do insert
        {
            inventory.insertStart(newItem);

            std::cout << std::endl << "Picked up " << item << ". It's now in your inventory." << std::endl << std::endl;

            return;
        }
        else               // if this is equipment, do swap
        {
            Helmet* helmet = dynamic_cast<Helmet*>(newEquipment);
            if(helmet)
            {
                //setHealth(getHealth() - (equipmentSet["helmet"] != nullptr ? equipmentSet["helmet"]->getValue() : 0));
                dropItem(helmet->name(), true);
                equipmentSet["helmet"] = helmet;
                setMaxHealth(maxHealth + equipmentSet["helmet"]->getValue());
                setHealth(getHealth() + helmet->getValue());
                std::cout << "You picked up " << helmet->name() << " and put it on!" << std::endl << std::endl;
                return;
            }
            Armor* armor = dynamic_cast<Armor*>(newEquipment);
            if(armor)
            {

                //setHealth(getHealth() - (equipmentSet["armor"] != nullptr ? equipmentSet["armor"]->getValue() : 0));
                dropItem(armor->name(), true);
                equipmentSet["armor"] = armor;
                setMaxHealth(maxHealth + equipmentSet["armor"]->getValue());
                setHealth(getHealth() + armor->getValue());
                std::cout << "You picked up " << armor->name() << " and put it on!" << std::endl << std::endl;
                return;
            }

            Greaves* greaves = dynamic_cast<Greaves*>(newEquipment);
            if(greaves)
            {

                //setHealth(getHealth() - (equipmentSet["greaves"] != nullptr ? equipmentSet["greaves"]->getValue() : 0));
                dropItem(greaves->name(), true);
                equipmentSet["greaves"] = greaves;
                setMaxHealth(maxHealth + equipmentSet["greaves"]->getValue());
                setHealth(getHealth() + greaves->getValue());
                std::cout << "You picked up " << greaves->name() << " and put it on!" << std::endl;
                return;
            }
            Weapon* weapon = dynamic_cast<Weapon*>(newEquipment);
            if(weapon)
            {
                dropItem(weapon->name(), true);
                equipmentSet["weapon"] = weapon;
                std::cout << "You wielded " << weapon->name() << "!" << std::endl << std::endl;
                return;
            }
        }
    }
    else
    {
        if(item.find("pot") != std::string::npos)
            std::cout << "Did you mean some sort of potion? You have to be more specific than that.." << std::endl << std::endl;
        else
            std::cout << "There doesn't seem to be that item in the room!" << std::endl << std::endl;
    }

}
void Character::print() const
{
    std::cout << std::endl <<  "-----------------------------------------------------------------------------------------------" << std::endl;
    _printAttributes();
    _printInventory();
    _printEquipmentSet();
    std::cout << std::endl <<  "-----------------------------------------------------------------------------------------------" << std::endl;
}

/* Manipulator */
void Character::setColPos(const int& col)
{
    if(col >= 0 && col < location->colBound)
        location->col = col;
}
void Character::setHealth(const int& newHealth)
{
    if(newHealth >= maxHealth) // 138 > 132? true
        health = maxHealth; // sets health to 132
    else
        health = newHealth; // 131 < 132
    if(health < 0)
        _die();
}

void Character::setInitialAttributes(const int& max)
{
    int temp = -1;
    std::string input;
    int totalBaseStat = max;
    std::cout << std::endl <<  "-----------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "You have " << totalBaseStat << " points to allocate into Strength (affecting damage), Intelligence (affecting healing), and Luck (affecting accuracy)" << std::endl << std::endl;
    do
    {
        std::cout << "Points remaining: " << totalBaseStat << std::endl;
        std::cout << "Enter number of points to allocate for strength: ";

        getline(std::cin, input);
        input.erase(remove_if(input.begin(), input.end(), [](char c) { return !isdigit(c); } ), input.end());
        try
        {
            temp = stoi(input);
        }
        catch(std::invalid_argument){ temp = -1; }
        catch(std::out_of_range) { temp = -1; }

        if(temp < 0 || temp > totalBaseStat || temp > max)
            std::cerr << "You can only allocate a maximum of " << totalBaseStat << " points!" << std::endl;
        else
        {
            setStrength(temp);
            totalBaseStat -= temp;
            temp = 0;
            break;
        }
    } while(temp < 0 || temp > totalBaseStat || temp > max);
    std::cout << "You allocated " << strength << " point" << (strength == 1 ? "" : "s") << " into strength." << std::endl << std::endl;
    do
    {
        if(totalBaseStat > 0)
        {
            std::cout << "Points remaining: " << totalBaseStat << std::endl;
            std::cout << "Enter number of points to allocate for intelligence: ";

            getline(std::cin, input);
            input.erase(remove_if(input.begin(), input.end(), [](char c) { return !isdigit(c); } ), input.end());

            try
            {
                temp = stoi(input);
            }
            catch(std::invalid_argument){ temp = -1; }
            catch(std::out_of_range) { temp = -1; }

            if(temp < 0 || temp > totalBaseStat || temp > max)
                std::cerr << "You can only allocate a maximum of " << totalBaseStat << " points!" << std::endl;
            else
            {
                setIntelligence(temp);
                std::cout << "You allocated " << intelligence << " point" << (intelligence == 1 ? "" : "s") << " into intelligence." << std::endl << std::endl;
                totalBaseStat -= temp;
                temp = 0;
                break;
            }
        }
        else
            std::cout << intelligence << " points were automatically allocated into intelligence." << std::endl << std::endl;
    }   while (temp < 0 || temp > totalBaseStat || temp > max);

    setLuck(totalBaseStat); // sets remaining
    std::cout << luck << " point" << (luck == 1 ? " was" : "s were") << " automatically allocated into luck." << std::endl;
    std::cout << "-----------------------------------------------------------------------------------------------" << std::endl;

}

void Character::setIntelligence(const int& intel)
{
    intelligence = intel;
}

void Character::setLuck(const int& luck)
{
    this->luck = luck;
}
void Character::setMaxHealth(const int& newMaxHealth)
{
    if(health == maxHealth)
        health = newMaxHealth;

    maxHealth = newMaxHealth;

    if(health > newMaxHealth)
        setHealth(newMaxHealth);

}
void Character::setName(const std::string& name)
{
    this->name = name;
}
void Character::setRowPos(const int& row)
{
    if(row >= 0 && row < location->rowBound)
        location->row = row;
}


void Character::setStrength(const int& str)
{
    strength = str;
}


void Character::useItem(const std::string& item)
{
    // check if item in inventory,
    int index = inventory.linearSearch(item);

    if (index != -1)
    {
        inventory.advanceToIndex(index);
        Item* itemPtr = inventory.getIterator();

        Potion* potionPtr = dynamic_cast<Potion*>(itemPtr);
        if (potionPtr)
        {
            int potionValue = potionPtr->getValue();
            std::string potionName = potionPtr->name();

            if (potionName == "health potion")
            {
                std::cout << "You took a sip from the health potion." << std::endl;
                if(health < maxHealth)
                    std::cout << "Your health increased by " << potionValue * ((getIntelligence() / 10.) + 1) << "." << std::endl;
                setHealth(getHealth() + potionValue * ((getIntelligence() / 10.) + 1));

            }
            else if (potionName == "max health potion")
            {
                std::cout << "You sipped the max health potion and you feel more energized." << std::endl;
                std::cout << "Max health increased by " << potionValue << "." << std::endl << std::endl;
                setMaxHealth(getMaxHealth() + potionValue);
            }
            else if (potionName == "strength potion")
            {
                std::cout << "You gulped down the strength potion and you feel stronger." << std::endl;
                std::cout << "Strength increased by " << potionValue << "." << std::endl << std::endl;
                setStrength(getStrength() + potionValue);
            }
            else if (potionName == "intelligence potion")
            {
                std::cout << "You look at the blue liquid and cautiously take a sip." << std::endl;
                std::cout << "Intelligence increased by " << potionValue << "." << std::endl << std::endl;
                setIntelligence(getIntelligence() + potionValue);
            }
            else if (potionName == "luck potion")
            {
                std::cout << "Ew, this looks disgusting. You drink it anyway." << std::endl;
                std::cout << "Luck increased by " << potionValue << "." << std::endl << std::endl;
                setLuck(getLuck() + potionValue);
            }
            delete potionPtr;               // remove iterator no longer realease memory
            inventory.removeIterator();      // remove the pointer from the linkedlist
            return;
        }

        KillScroll* killScrollPtr = dynamic_cast<KillScroll*>(itemPtr);
        if (killScrollPtr) // isn't this when monster exists?  // i don't know who wrote this but _useKillScroll() checks for monster existing or not.
        {
            _useKillScroll();
            killScrollPtr = nullptr;
            inventory.removeIterator();
            return;
        }
        else
        {
            std::cout << "You can not use that item directly." << std::endl << std::endl;
            return;
        }

    }
    else
    {
        if(item == "fountain" || item == "treasure" || item == "book" || item == "map" || item == "flare")
            std::cout << "Did you mean 'activate'?" << std::endl << std::endl;
        else
            std::cout << "You don't have that item, pal!" << std::endl << std::endl;
    }
}
