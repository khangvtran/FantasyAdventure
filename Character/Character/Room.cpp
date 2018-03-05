/*
 
 Implementation file for the Room class.
 
 */

#include "Room.h"

/********************************************************************************************
 Constructor
 Initializes room data to starting values.
 *******************************************************************************************/
Room::Room(int row, int col, unsigned char wall)
{
    //Set row, col, and wall data
    setCoordinates(row, col);
    setWalls(wall);
    
    //Set Monster and RoomObject pointers to NULL
    setMonsterPtr();
    setRoomObjectPtr();
}

/********************************************************************************************
 Destructor
 Releases dynamic memory used by monster, room object and item objects.
 *******************************************************************************************/
Room::~Room()
{
    if (monsterPtr)
    {
        delete monsterPtr;
    }
    
    if (roomObjectPtr)
    {
        delete roomObjectPtr;
    }
    
    if (!items.empty())
    {
        for (int i = 0; i < items.size(); i++)
        {
            delete items[i];
        }
        items.erase(items.begin());
    }
}

/********************************************************************************************
 checkNorth
 Returns true if movement north is possible. (i.e. no wall exists to the north of player's
 position) Wall data is stored in the last nibble of an unsigned char in the following bit
 pattern: 0000 W E S N
 *******************************************************************************************/
bool Room::checkNorth() const
{
    //Mask: 0000 0001
    const unsigned char MASK = 1;
    
    if (walls & MASK)
    {
        //cout << "wall: " << static_cast<unsigned>(walls) << " mask: " << static_cast<unsigned>(MASK) << endl;
        //cout << "Result: " << boolalpha << (walls & MASK) << endl;
        //Wall -> character cannot move north
        return false;
    }
    
    //No wall -> character can move north
    return true;
}

/********************************************************************************************
 checkSouth
 Returns true if movement south is possible. (i.e. no wall exists to the north of player's
 position) Wall data is stored in the last nibble of an unsigned char in the following bit
 pattern: 0000 W E S N
 *******************************************************************************************/
bool Room::checkSouth() const
{
    //Mask: 0000 0010
    const unsigned char MASK = 2;
    
    if (walls & MASK)
    {
        //cout << "wall: " << static_cast<unsigned>(walls) << " mask: " << static_cast<unsigned>(MASK) << endl;
        //cout << "Result: " << boolalpha << (walls & MASK) << endl;
        //Wall -> character cannot move north
        return false;
    }
    
    //No wall -> character can move north
    return true;
}

/********************************************************************************************
 checkEast
 Returns true if movement west is possible. (i.e. no wall exists to the north of player's
 position) Wall data is stored in the last nibble of an unsigned char in the following bit
 pattern: 0000 W E S N
 *******************************************************************************************/
bool Room::checkEast() const
{
    //Mask: 0000 0100
    const unsigned char MASK = 4;
    
    if (walls & MASK)
    {
        //cout << "wall: " << static_cast<unsigned>(walls) << " mask: " << static_cast<unsigned>(MASK) << endl;
        //cout << "Result: " << boolalpha << (walls & MASK) << endl;
        //Wall -> character cannot move north
        return false;
    }
    
    //No wall -> character can move north
    return true;
}

/********************************************************************************************
 checkWest
 Returns true if movement west is possible. (i.e. no wall exists to the north of player's
 position) Wall data is stored in the last nibble of an unsigned char in the following bit
 pattern: 0000 W E S N
 *******************************************************************************************/
bool Room::checkWest() const
{
    //Mask: 0000 1000
    const unsigned char MASK = 8;
    
    if (walls & MASK)
    {
        //cout << "wall: " << static_cast<unsigned>(walls) << " mask: " << static_cast<unsigned>(MASK) << endl;
        //cout << "Result: " << boolalpha << (walls & MASK) << endl;
        //Wall -> character cannot move north
        return false;
    }
    
    //No wall -> character can move north
    return true;
}

/********************************************************************************************
 contains
 Searches items vector for a specific item. Returns true if the item is found.
 *******************************************************************************************/
bool Room::contains(string s)
{
    if (!(items.empty()))
    {
        for (int i = 0; i < items.size(); i++)
        {
            Item* temp = items[i];
            if (temp->name() == s)
            {
                return true;
            }
        }
    }
    
    return false;
}

/********************************************************************************************
 removeItem
 Removes a specific item from the vector of items. Returns nullptr if item is not found.
 *******************************************************************************************/
Item* Room::removeItem(string anItem)
{
    
    if (!(items.empty()))
    {
        //Step through the vector and search for the item
        for (int i = 0; i < items.size(); i++)
        {
            Item* temp = items[i];
            if (temp->name() == anItem)
            {
                //If you found the item erase it from the items vector
                items.erase (items.begin()+ i);
                return temp;
            }
        }
    }
    //If item is not found, return nullptr
    return nullptr;
}

/********************************************************************************************
 setDescription
 Generates room description based on intialized pointers.
 *******************************************************************************************/
void Room::setDescription()
{
    //cout << "WALLS: " << static_cast<unsigned>(walls) << endl;
    if (getMonsterPtr() || getRoomObjectPtr() || (!items.empty()))
    {
        if (getMonsterPtr())
        {
            cout << "monster" << endl;
            description = "In this room you find a(n) " + getMonsterPtr()->getName() + ".\n" + getMonsterPtr()->getDescription() + "\n";
        }
        else if (getRoomObjectPtr())
        {
            description = "In this room you find a(n) " + getRoomObjectPtr()->getName() + ".\n" + getRoomObjectPtr()->getDescription() + "\n";
        }
        else if(!items.empty())
        {
            description = "In this room you find a(n) ";
            for (int i = 0; i < items.size(); i++)
            {
                Item* temp = items[i];
                {
                    description += temp->name() + " ";
                    description += temp->description() + "\n";
                }
            }
        }
    }
    else
    {
        description = "This room is empty.\n";
    }
}

/********************************************************************************************
 Overloaded ostream<< Operator
 Prints room data.
 *******************************************************************************************/
ostream& operator<<(ostream& strm, const Room& room)
{
    strm << "row: " << setw(2) << room.coordinates.row << " col: " << setw(2) << room.coordinates.col << " walls: "
    << setw(2) << static_cast<int>(room.walls) << boolalpha << " MonsterPtr: " << setw(20) << room.getMonsterPtr()
    << setw(20) << " RoomObjectPtr: " << setw(20) << room.getRoomObjectPtr() << " Items: " <<  setw(5) << room.items.empty() << endl;
    
    return strm;
}

