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
 Releases dynamic memory used by monster, room object and item list.
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
        for (auto listIt = items.cbegin(); listIt != items.cend(); ++listIt)
        {
            delete *listIt;
        }
        items.clear();
    }
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
 Searches items list for a specific item. Returns true if the item is found.
 *******************************************************************************************/
bool Room::contains(const std::string& s)
{
    if (!(items.empty()))
    {
        std::list<Item*>::const_iterator it;
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
 setCoordinates
 Sets room's row and col coordinates.
 *******************************************************************************************/
void Room::setCoordinates (int r, int c)
{
    coordinates.row = r;
    coordinates.col = c;
}
/********************************************************************************************
 setItem
 Adds an Item pointer to the list of items.
 *******************************************************************************************/
void Room::setItem(Item* iptr)
{
    if (iptr != nullptr)
    {
        items.push_back(iptr);
    }
}

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
 setWalls
 Sets room's wall data stored as an unsigned char.
 *******************************************************************************************/
void Room::setWalls(unsigned char w)
{
    walls = w;
};

/********************************************************************************************
 getCol
 Returns col coordinate.
 *******************************************************************************************/
int Room::getCol() const
{
    return coordinates.col;
}

/********************************************************************************************
 getItems
 Returns a list of item pointers if at least one item object is present in the room.
 *******************************************************************************************/
std::list<Item*> Room::getItems() const
{
    return items;
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
 getRoom
 Returns a pointer to the current room.
 *******************************************************************************************/
Room& Room::getRoom()
{
    return *this;
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
 getRoomCoordinates
 Returns a reference to a struct with room coordinate.
 *******************************************************************************************/
const RoomCoordinates& Room::getRoomCoordinates() const
{
    return coordinates;
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
 getWalls
 Returns an unsigned char storing wall data.
 *******************************************************************************************/
const unsigned char Room::getWalls() const
{
    return walls;
}

/********************************************************************************************
 removeItem
 Searches for and removes a specific item from the list of items. If item is found, returns
 a pointer to the item. If item is not found, returns nullptr.
 *******************************************************************************************/
Item* Room::removeItem(const std::string& anItem)
{
    Item* temp = nullptr;       //Store pointer to the searched item
    //cout << "temp: " << temp << endl;             //DEBUG
    if (!(items.empty()))
    {
        //Step through the list and search for the item
        std::list<Item*>::const_iterator it;
        for (it = items.cbegin(); it != items.cend(); ++it)
        {
            if ((*it)->name() == anItem)
            {
                //If found, store item pointer to be returned
                temp = *it;
                
                //Erase the item from list
                items.erase(it);
                break;
            }
        }
    }

    //Return pointer to the searched item
    return temp;
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
 Overloaded ostream<< Operator
 Prints room description and data.
 *******************************************************************************************/
std::ostream& operator<<(std::ostream& strm, const Room& room)
{
    std::cout << std::setw(100) << "~~~~~~~~~~~~********** **** ********** ~~~~~~~~~~~~" << std::endl << std::endl;
    std::cout << std::setw(70) << "Room: " << "[row: " << room.getRow() << "] " << "[col: " << room.getCol() << "]" << std::endl;
    std::cout << std::setw(70);
    if (room.getMonsterPtr() || room.getRoomObjectPtr() || (!room.items.empty()))
    {
        if (room.getMonsterPtr())
        {
            strm << "\n" << std::endl;
            strm << std::left << std::setw(80) << ("In this room you find a(n) " + room.getMonsterPtr()->getName()) << std::endl;
            strm << std::setw(80) << room.getMonsterPtr()->getDescription() << std::endl;
            std::cout << "\n" << std::endl;
        }
        else if (room.getRoomObjectPtr() || (!room.items.empty()))
        {
            if (room.getRoomObjectPtr())
            {
                strm << "\n" << std::endl;
                strm << std::left << std::setw(80) << ("In this room you find a(n) " + room.getRoomObjectPtr()->getName()) << std::endl;
                strm << std::setw(80) << room.getRoomObjectPtr()->getDescription() << std::endl;
                strm << "\n" << std::endl;
            }
            if (!room.items.empty())
            {
                strm << "\n" << std::endl;
                strm << std::left << std::setw(20) << "In this room you find a(n) ";

                if (room.items.size() == 1)
                {
                    strm << room.items.front()->name() << " : " << room.items.front()->description() << std::endl;
                }
                else
                {
                    std::cout << std::endl;
                    for (auto i: room.items)
                    {
                        {
                            strm << " - ";
                            strm << i->name();
                            strm << " : ";
                            strm << i->description();
                            std::cout << std::endl;
                        }
                    }
                }
                std::cout << std::endl;
            }
        }
    }
    else
    {
        strm << "\n" << std::endl;
        strm <<  "This room is empty.";
        strm << "\n" << std::endl;
    }

    std::cout << std::right << std::setw(100) << "~~~~~~~~~~~~********** **** ********** ~~~~~~~~~~~~" << std::endl << std::endl;

    return strm;
}

