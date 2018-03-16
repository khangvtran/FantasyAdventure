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
Character::Character(const string& Name, const int& row, const int& col, Dungeon& dungeon) : name(Name), dungeon(&dungeon), strength(0), intelligence(0), luck(0), alive(true), lives(3)
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
    

    cout << *currentRoom;
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
            cout << "Maybe it's just me but do you see that colossal monster guarding the treasure there, mate??" << endl;
            return;
        }
        // check if all gems are in itemList
        if (inventory.linearSearch("ruby") == -1 || inventory.linearSearch("sapphire") == -1 || inventory.linearSearch("emerald") == -1)
        {
            cout << "You still have to acquire all three gems: ruby, sapphire, and emerald" << endl;
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
    cout << endl << endl << "***** YOU DIED *****" << endl << endl;
    cout << "What a shame.. Should've tried harder than that!" << endl;
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
            cout << "You're on your last life! What are you doing‽" << endl;
        else
        {
            cout << "Luckily, you seem to have " << lives;
            if(lives > 1)
                cout << " lives";
            else
                cout  << " life";
             cout << " remaining." << endl;
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
                cout << "You were lucky this time! Your health increased from " << health;
                setHealth(health + 3 * intelligence);
                cout << " to " << health << "." << endl << endl;
            }
            else
                cout << "The fountain would've healed you... but you were already at full health.";
        }
        else
        {
            cout << "Ouch! That water might have been slightly poisonous. You lost 10 health." << endl;
            cout << "Your health decreased from " << health << " to " << health - 10 << "." << endl;
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
        setColPos(location->col+1);
        currentRoom = &(dungeon->getRoom(location->row, location->col));
    }
    else // exception, handled by main
        throw AdventureErrors::InvalidMove("There's a wall in the East direction!");
}

void Character::_moveNorth() throw(AdventureErrors::InvalidMove)
{
    if(currentRoom->checkNorth())
    {
        setRowPos(location->row-1);
        currentRoom = &(dungeon->getRoom(location->row, location->col));
    }
    else // exception, handled by main
        throw AdventureErrors::InvalidMove("There's a wall in the North direction!");
}

void Character::_moveSouth() throw(AdventureErrors::InvalidMove)
{
    if(currentRoom->checkSouth())
    {
        setRowPos(location->row+1);
        currentRoom = &(dungeon->getRoom(location->row, location->col));
    }
    else // exception, handled by main
        throw AdventureErrors::InvalidMove("There's a wall in the South direction!");
}

void Character::_moveWest() throw(AdventureErrors::InvalidMove)
{
    if(currentRoom->checkWest())
    {
        setColPos(location->col-1);
        currentRoom = &(dungeon->getRoom(location->row, location->col));
    }
    else // exception, handled by main
        throw AdventureErrors::InvalidMove("There's a wall in the West direction!");
}




void Character::_printAttributes() const
{
    cout << "Character Attributes: " << endl;
    cout << "Lives remaining: " << lives << endl;
    cout << "Health: " << health << endl;
    cout << "Max Health: " << maxHealth << endl;
    cout << "Strength: " << strength << endl;
    cout << "Intelligence: " << intelligence << endl;
    cout << "Luck: " << luck << endl;
    cout << endl;
}

void Character::_printEquipmentSet() const
{
    if(equipmentSet.size() > 0)
        cout << "Character Equipment: " << endl;
    try
    {
        if(equipmentSet.at("helmet")!= nullptr)
            cout << equipmentSet.at("helmet")->name() << " (+" << equipmentSet.at("helmet")->getValue() << " max health)"<< endl;
        if(equipmentSet.at("armor")!= nullptr)
            cout << equipmentSet.at("armor")->name() << " (+" << equipmentSet.at("armor")->getValue() << " max health)"<< endl;
        if(equipmentSet.at("greaves")!= nullptr)
            cout << equipmentSet.at("greaves")->name() << " (+" << equipmentSet.at("greaves")->getValue() << " max health)"<< endl;
        if(equipmentSet.at("weapon")!= nullptr)
            cout << setprecision(2) << equipmentSet.at("weapon")->name() << " (+" << equipmentSet.at("weapon")->getValue() << " damage)";
        if(equipmentSet.at("weapon")!= nullptr && dynamic_cast<Dagger*>(equipmentSet.at("weapon")) != nullptr)
            cout << " [Chance to do critical hit! (x2)]";

    } catch (out_of_range &err)
    {
        cerr << err.what() << endl;
    }

}

void Character::_printInventory() const
{
    if(!inventory.isEmpty())
    {
        cout << "Character Inventory: " << endl;
        inventory.printNumberedList();
        cout << endl;
    }
}

/**
 Calculates an accuracy range based on character's luck (MAX LUCK = 18, ACCURACY == 100%, Total initial Atrributes = 18)
 Returns true if character's attack will NOT miss
 Returns false if character's attack WILL miss
 */
bool Character::_randomizer() const // CHANGE: AccuracyHit() changed into HitOrHeal()
{
    double accuracyRange = pow(luck, log10(100)/log10(16/* "MAX LUCK"*/));
    return (rand()%100 <= accuracyRange);
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
        string cmd = "";
        do
        {
            cout << endl << "Which map would you like to view? [basic, monster, roomobject, item, all]: ";
            cin >> cmd;
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

        cin.ignore(10, '\n');
        cin.clear();
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
        cout << "There is no monster. What are you using that kill scroll for, pal? " << endl;
        return;
    }
    else
    {
        m->modifyHealth(m->getHealth() + 1);    // kill the monster
        currentRoom->removeMonster();           // remove monster from the room
        cout << *currentRoom;
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
        cout << endl << "There's no monster in the room." << endl;
        return;
    }
    if(_randomizer())
    {
        double modifier = (equipmentSet["weapon"] != nullptr ? equipmentSet["weapon"]->getValue() : 1);
        double damage = 1.2 * strength + modifier;
        if(_randomizer() && dynamic_cast<Dagger*>(equipmentSet.at("weapon")) != nullptr)
        {
            cout << "Your dagger dealt double damage to " << m->getName() << "!" << endl;
            damage *= 2;
        }
        // put in miss cout
        cout << endl << "You dealt " << static_cast<int>(damage) << " damage to " << m->getName() << "." << endl;
        if(!m->modifyHealth(damage))
        {
            currentRoom->removeMonster(); // modify health COULD return a true/false to indicate monster is alive or dead, then we can call ROOM's REMOVE on monster to set to nullptr
            cout << *currentRoom; // ADDED
            return;
        }
    }
    else
        cout << endl << "You missed the " << m->getName() << " this time around!" << endl;
    double monsterDamage = m->attack(luck);
    if(monsterDamage != 0)
    {
        setHealth(health - monsterDamage);
        cout << "Your health is now: " << health << endl << endl;
    }
    else
        cout << endl << endl;

    if(!isAlive())
        throw AdventureErrors::CharacterDeath("You messed up. You definitely didn't win this time!"); //throw exception (died);

}


void Character::activate(const string& thing) throw(AdventureErrors::MissingObject, AdventureErrors::CharacterDeath)
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
        cout << "You can't activate that!";
    cout << endl << endl;
}

void Character::cheat(const string& cmd, const string& cmd2)
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
        std::istringstream is(cmd2);
        int row = 0, col = 0;
        is >> row >> col;
        setRowPos(row);
        setColPos(col);
        cout << "Teleported to (" << location->row << "," << location->col << ")." << endl;
        currentRoom = &(this->dungeon->getRoom(location->row, location->col));
        cout << *currentRoom;
    }
    else if(cmd == "spawn")
    {
        Generation spawner;
        try {
            Item* thing = spawner.generateItem(spawner.itemContainer.at(cmd2));
            currentRoom->setItem(thing);
            if(currentRoom->getMonsterPtr() != nullptr)
                cout << thing->name() << " was spawned on the ground. \nYou can't pick it up until you kill the " << currentRoom->getMonsterPtr()->getName() << " though." << endl << endl;
            else
                pickupItem(thing->name());
        } catch (out_of_range &err) {
            cerr << "Invalid type " << cmd2 << "." << endl << endl;
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
void Character::dropItem(const string& item, bool fromPickup)
{
    size_t spacePos = item.find(" ");
    string secondWord = item.substr(spacePos+1);
    if(secondWord == "armor")
    {
        Equipment* armor = equipmentSet["armor"];
        if(armor != nullptr)
        {
            if((health - armor->getValue()) <= 0)
            {
                cout << "Are you sure you want to drop that? Your health is dangerously low." << endl << endl;
                return;
            }
            if(item == armor->name() || fromPickup)
            {
                cout << "Dropped " << armor->name() << " on the ground." << endl << endl;
                setMaxHealth(maxHealth - armor->getValue());
                currentRoom->setItem(armor);
                equipmentSet["armor"] = nullptr;
                cout << *currentRoom;
                return;
            }
            else
                 cout << "You have to be more specific than that! Did you mean " << armor->name() << "?" << endl << endl;
        }
        else
            cout << "You got no armor to drop." << endl << endl;
    }
    else if(secondWord == "helmet")
    {
        Equipment* helmet = equipmentSet["helmet"];
        if(helmet != nullptr)
        {
            if((health - helmet->getValue()) <= 0)
            {
                cout << "Are you sure you want to drop that? Your health is dangerously low." << endl << endl;
                return;
            }
            if(item == helmet->name() || fromPickup)
            {
                cout << "Dropped " << helmet->name() << " on the ground." << endl << endl;
                setMaxHealth(maxHealth - helmet->getValue());
                currentRoom->setItem(helmet);
                equipmentSet["helmet"] = nullptr;
                cout << *currentRoom;
                return;
            }
            else
                 cout << "You have to be more specific than that! Did you mean " << helmet->name() << "?" << endl << endl;
        }
        else
            cout << "You got no helmet to drop." << endl << endl;
    }
    else if(secondWord == "greaves")
    {
        Equipment* greaves = equipmentSet["greaves"];
        if(greaves != nullptr)
        {
            if((health - greaves->getValue()) <= 0)
            {
                cout << "Are you sure you want to drop that? Your health is dangerously low." << endl << endl;
                return;
            }
            if(item == greaves->name() || fromPickup)
            {
                cout << "Dropped " << greaves->name() << " on the ground." << endl << endl;
                setMaxHealth(maxHealth - greaves->getValue());
                currentRoom->setItem(greaves);
                equipmentSet["greaves"] = nullptr;
                cout << *currentRoom;
                return;
            }
            else
                cout << "You have to be more specific than that! Did you mean " << greaves->name() << "?" << endl << endl;
        }
        else
            cout << "You got no greaves to drop." << endl << endl;
    }
    else if(secondWord == "sword" || secondWord == "dagger")
    {
        Equipment* weapon = equipmentSet["weapon"];
        if(weapon != nullptr)
        {
            if(item == weapon->name() || fromPickup)
            {
                cout << "Dropped " << equipmentSet["weapon"]->name() << " on the ground." << endl << endl;
                currentRoom->setItem(equipmentSet["weapon"]);
                equipmentSet["weapon"] = nullptr;
                cout << *currentRoom;
                return;
            }
            else
                cout << "You have to be more specific than that! Did you mean " << weapon->name() << "?" << endl << endl;
        }
        else
            cout << "You got no weapon to drop." << endl << endl;
    }
    else
    {
        int index = inventory.linearSearch(item);
        if(index != -1)
        {
            inventory.advanceToIndex(index);
            currentRoom->setItem(inventory.getIterator());
            inventory.removeIterator();
            cout << "Removed " << item << " from inventory. It's on the ground now." << endl << endl; // debugging
            cout << *currentRoom;
        }
        else
            cout << "Are you really sure you have " << item << " in your inventory?" << endl;
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
    } catch (out_of_range &err)
    {
        cerr << err.what() << endl;
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
string Character::getName() const
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

void Character::move(const string& direction) throw(AdventureErrors::InvalidMove)
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
            throw AdventureErrors::InvalidMove(string("Invalid move direction: " +direction).c_str());
    } catch (AdventureErrors::InvalidMove) {
        throw;
    }
    cout << endl << endl;
    cout << *currentRoom;
}

 /* Interaction with Items - Equipment */
void Character::pickupItem(const string& item)
{
    if (currentRoom->getMonsterPtr() != nullptr)
    {
        cout << "Waste the guarding monster first. No pain no gain, pal." << endl << endl;
        return;
    }

    if (currentRoom->contains(item))                    // check if there is an item
    {
        Item* newItem = currentRoom->removeItem(item);  // take the item from the room

        Equipment* newEquipment = dynamic_cast<Equipment*>(newItem); // downcast into equipment

        if (!newEquipment) // if this is consumable item, do insert
        {
            inventory.insertStart(newItem);

            cout << endl << "Picked up " << item << ". It's now in your inventory." << endl << endl;

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
                cout << "You picked up " << helmet->name() << " and put it on!" << endl << endl;
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
                cout << "You picked up " << armor->name() << " and put it on!" << endl << endl;
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
                cout << "You picked up " << greaves->name() << " and put it on!" << endl;
                return;
            }
            Weapon* weapon = dynamic_cast<Weapon*>(newEquipment);
            if(weapon)
            {
                dropItem(weapon->name(), true);
                equipmentSet["weapon"] = weapon;
                cout << "You wielded " << weapon->name() << "!" << endl << endl;
                return;
            }
        }
    }
    else
    {
        if(item.find("pot") != string::npos)
            cout << "Did you mean some sort of potion? You have to be more specific than that.." << endl << endl;
        else
            cout << "There doesn't seem to be that item in the room!" << endl << endl;
    }

}
void Character::print() const
{
    cout << endl <<  "-----------------------------------------------------------------------------------------------" << endl;
    _printAttributes();
    _printInventory();
    _printEquipmentSet();
    cout << endl <<  "-----------------------------------------------------------------------------------------------" << endl;
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
    string input;
    int totalBaseStat = max;
    cout << endl <<  "-----------------------------------------------------------------------------------------------" << endl;
    cout << "You have " << totalBaseStat << " points to allocate into Strength (affecting damage), Intelligence (affecting healing), and Luck (affecting accuracy)" << endl << endl;
    do
    {
        cout << "Points remaining: " << totalBaseStat << endl;
        cout << "Enter number of points to allocate for strength: ";

        getline(cin, input);
        input.erase(remove_if(input.begin(), input.end(), [](char c) { return !isdigit(c); } ), input.end());
        try
        {
            temp = stoi(input);
        }
        catch(invalid_argument){ temp = -1; }
        catch(out_of_range) { temp = -1; }

        if(temp < 0 || temp > totalBaseStat || temp > max)
            cerr << "You can only allocate a maximum of " << totalBaseStat << " points!" << endl;
        else
        {
            setStrength(temp);
            totalBaseStat -= temp;
            temp = 0;
            break;
        }
    } while(temp < 0 || temp > totalBaseStat || temp > max);
    cout << "You allocated " << strength << " point" << (strength == 1 ? "" : "s") << " into strength." << endl << endl;
    do
    {
        if(totalBaseStat > 0)
        {
            cout << "Points remaining: " << totalBaseStat << endl;
            cout << "Enter number of points to allocate for intelligence: ";

            getline(cin, input);
            input.erase(remove_if(input.begin(), input.end(), [](char c) { return !isdigit(c); } ), input.end());

            try
            {
                temp = stoi(input);
            }
            catch(invalid_argument){ temp = -1; }
            catch(out_of_range) { temp = -1; }

            if(temp < 0 || temp > totalBaseStat || temp > max)
                cerr << "You can only allocate a maximum of " << totalBaseStat << " points!" << endl;
            else
            {
                setIntelligence(temp);
                cout << "You allocated " << intelligence << " point" << (intelligence == 1 ? "" : "s") << " into intelligence." << endl << endl;
                totalBaseStat -= temp;
                temp = 0;
                break;
            }
        }
        else
            cout << intelligence << " points were automatically allocated into intelligence." << endl << endl;
    }   while (temp < 0 || temp > totalBaseStat || temp > max);

    setLuck(totalBaseStat); // sets remaining
    cout << luck << " point" << (luck == 1 ? " was" : "s were") << " automatically allocated into luck." << endl;
    cout << "-----------------------------------------------------------------------------------------------" << endl;

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
void Character::setName(const string& name)
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


void Character::useItem(const string& item)
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
            string potionName = potionPtr->name();

            if (potionName == "health potion")
            {
                cout << "You took a sip from the health potion." << endl;
                if(health < maxHealth)
                    cout << "Your health increased by " << potionValue * ((getIntelligence() / 10.)+1) << "." << endl;
                setHealth(getHealth() + potionValue * ((getIntelligence() / 10.)+1));

            }
            else if (potionName == "max health potion")
            {
                cout << "You sipped the max health potion and you feel more energized." << endl;
                cout << "Max health increased by " << potionValue << "." << endl << endl;
                setMaxHealth(getMaxHealth() + potionValue);
            }
            else if (potionName == "strength potion")
            {
                cout << "You gulped down the strength potion and you feel stronger." << endl;
                cout << "Strength increased by " << potionValue << "." << endl << endl;
                setStrength(getStrength() + potionValue);
            }
            else if (potionName == "intelligence potion")
            {
                cout << "You look at the blue liquid and cautiously take a sip." << endl;
                cout << "Intelligence increased by " << potionValue << "." << endl << endl;
                setIntelligence(getIntelligence() + potionValue);
            }
            else if (potionName == "luck potion")
            {
                cout << "Ew, this looks disgusting. You drink it anyway." << endl;
                cout << "Luck increased by " << potionValue << "." << endl << endl;
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
            cout << "You can not use that item directly." << endl << endl;
            return;
        }

    }
    else
    {
        if(item == "fountain" || item == "treasure" || item == "book" || item == "map" || item == "flare")
            cout << "Did you mean 'activate'?" << endl << endl;
        else
            cout << "You don't have that item, pal!" << endl << endl;
    }
}
