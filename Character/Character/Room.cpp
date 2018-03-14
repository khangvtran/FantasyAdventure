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
        for (auto i = 0; i < items.size(); i++)
        {
            delete items[i];
        }
        items.erase(items.begin());
    }
}

/********************************************************************************************
 setCoordinates
 Sets room's row and col coordinates.
 *******************************************************************************************/
void Room::setCoordinates (int r, int c)
{
    coordinates.row = r;
    coordinates.col = c;
}

/********************************************************************************************
 setWalls
 Sets room's wall data stored as an unsigned char.
 *******************************************************************************************/
void Room::setWalls(unsigned char w)
{
    walls = w;
};

/********************************************************************************************
 setMonsterPtr
 Initializes MonsterPtr with an address of a Monster object.
 *******************************************************************************************/
void Room::setMonsterPtr(Monster* mptr)
{
    monsterPtr = mptr;
}

/********************************************************************************************
 setRoomObjectPtr
 Initializes RoomObjectPtr with an address of a RoomObject object.
 *******************************************************************************************/
void Room::setRoomObjectPtr(RoomObject* roptr)
{
    roomObjectPtr = roptr;
}

/********************************************************************************************
 setItem
 Adds an Item pointer to the vector of items.
 *******************************************************************************************/
void Room::setItem(Item* iptr)
{
    if (iptr != nullptr)
    {
        items.push_back(iptr);
    }
}

/********************************************************************************************
 removeMonster
 Removes a monster from the room by deleting the monster object and setting MonsterPtr to NULL.
 *******************************************************************************************/
void Room::removeMonster()
{
    delete monsterPtr;
    monsterPtr = nullptr;
}

/********************************************************************************************
 getRow
 Returns row coordinate.
 *******************************************************************************************/
int Room::getRow() const
{
    return coordinates.row;
}

/********************************************************************************************
 getCol
 Returns col coordinate.
 *******************************************************************************************/
int Room::getCol() const
{
    return coordinates.col;
}

/********************************************************************************************
 getRoomCoordinates
 Returns a reference to a struct with room coordinate.
 *******************************************************************************************/
const RoomCoordinates& Room::getRoomCoordinates() const
{
    return coordinates;
}

/********************************************************************************************
 getWalls
 Returns an unsigned char storing wall data.
 *******************************************************************************************/
const unsigned char Room::getWalls() const
{
    return walls;
}

/********************************************************************************************
 getMonsterPtr
 Returns a pointer to a monster if monster is present in the room. Returns nullptr otherwise.
 *******************************************************************************************/
Monster* Room::getMonsterPtr() const
{
    return monsterPtr;
}

/********************************************************************************************
 getRoomObjectPtr
 Returns a pointer to a monster if monster is present in the room. Returns nullptr otherwise.
 *******************************************************************************************/
RoomObject* Room::getRoomObjectPtr() const
{
    return roomObjectPtr;
}

/********************************************************************************************
 getItems
 Returns a vector of item pointers if at least one item object is present in the room.
 *******************************************************************************************/
vector<Item*> Room::getItems() const
{
    return items;
}

/********************************************************************************************
 getRoom
 Returns a pointer to the current room.
 *******************************************************************************************/
Room& Room::getRoom()
{
    return *this;
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
        return false;
    }
    
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
        return false;
    }
 
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
        return false;
    }

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
        return false;
    }

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
        vector<Item*>::const_iterator it;
        for (it = items.cbegin(); it != items.cend(); ++it)
        {
            if ((*it)->name() == s)
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
        vector<Item*>::const_iterator it;
        for (it = items.cbegin(); it != items.cend(); ++it)
        {
            if ((*it)->name() == anItem)
            {
                //If you found the item erase it from the items vector
                items.erase(it);
                
                //Return pointer to the item
                return *it;
            }
        }
    }
    //If item is not found, return nullptr
    return nullptr;
}

/********************************************************************************************
 Overloaded ostream<< Operator
 Prints room description and data.
 *******************************************************************************************/
ostream& operator<<(ostream& strm, const Room& room)
{
    cout << setw(100) << "~~~~~~~~~~~~********** **** ********** ~~~~~~~~~~~~" << endl << endl;
    cout << setw(70) << "Room: " << "[row: " << room.getRow() << "] " << "[col: " << room.getCol() << "]" << endl;
    cout << setw(70);
    if (room.getMonsterPtr() || room.getRoomObjectPtr() || (!room.items.empty()))
    {
        if (room.getMonsterPtr())
        {
            strm << "\n" << endl;
            strm << left << setw(80) << ("In this room you find a(n) " + room.getMonsterPtr()->getName()) << endl;
            strm << setw(80) << room.getMonsterPtr()->getDescription() << endl;
            cout << "\n" << endl;
        }
        else if (room.getRoomObjectPtr() || (!room.items.empty()))
        {
            if (room.getRoomObjectPtr())
            {
                strm << "\n" << endl;
                strm << left << setw(80) << ("In this room you find a(n) " + room.getRoomObjectPtr()->getName()) << endl;
                strm << setw(80) << room.getRoomObjectPtr()->getDescription() << endl;
                strm << "\n" << endl;
            }
            if (!room.items.empty())
            {
                strm << "\n" << endl;
                strm << left << setw(20) << "In this room you find a(n) ";

                if (room.items.size() == 1)
                {
                    strm << room.items[0]->name() << " : " << room.items[0]->description() << endl;
                }
                else
                {
                    cout << endl;
                    for (auto i: room.items)
                    {
                        {
                            strm << " - ";
                            strm << i->name();
                            strm << " : ";
                            strm << i->description();
                            cout << endl;
                        }
                    }
                }
                cout << endl;
            }
        }
    }
    else
    {
        strm << "\n" << endl;
        strm <<  "This room is empty.";
        strm << "\n" << endl;
    }
    
    cout << right << setw(100) << "~~~~~~~~~~~~********** **** ********** ~~~~~~~~~~~~" << endl << endl;
    
    return strm;
}

