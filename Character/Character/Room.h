/*
 
 Specification file for the Room class.
 
 A Room is one Dungeon (matrix) unit that can be entered, traversed and exited by the player according the Dungeon layout.
 
 Implementation:
 
 Data:
 RoomCoordinates - a struct that holds each room's col and row coordinates
 walls - an 8-bit unsigned char that stores wall data in the last nibble (4 bits)
 description - a string storing room description
 monsterPtr - a pointer to a monster object
 roomObjectPtr - a pointer to a room object
 Items - a vector of pointers to items
 
 
 Functions:
 Constructor - sets room data
 Destructor - resets pointers to objects present in the room to NULL
 setCoordinates - sets room coordinates
 setWalls - sets wall data
 setMonsterPtr - initializes monster pointer to an address of a Monster object if a monster is present in the room
 setRoomObjectPtr - initializes monster pointer to an address of a RoomObject object if a room object is present in the room
 setItems - initializes a vector of Item pointers to addresses of Item objects if they are present in the room
 setDescription - sets room description
 
 getRoomCoordinates - returns a struct with room coordinates
 getWalls - returns an unsigned char storing wall positions in the last nibble
 getMonster - returns a pointer to a Monster object present in the room
 getRoomObject - returns a pointer to a RoomObject if a room object is present in the room
 getItems - returns a vector of pointers to items if items are present in the room
 getRoom - returns a reference to a room
 getDescription - displays the room description
 checkNorth - returns true if movement northwards is possible (no wall is present)
 checkSouth - returns true if movement southwards is possible (no wall is present)
 checkEast - returns true if movement eastwards is possible (no wall is present)
 checkWest - returns true if movement westwards is possible (no wall is present)
 print - prints room walls
 Overloaded Operator<< - prints the contents of a room
 
 */

#ifndef Room_h
#define Room_h

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Monster.h"
#include "RoomObject.h"
#include "Item.h"
using namespace std;

class Room
{
private:
    //Room coordinates & wall data
    struct RoomCoordinates
    {
        int row;
        int col;
    };
    RoomCoordinates coordinates;                             //Room ID represented by row and col coordinates
    unsigned char walls;                                     //stores wall positions in the last nibble of the 8-bit unsigned char
    
    //Pointers to monster, room object and vector of items
    Monster* monsterPtr;                                     //stores a pointer to a monster
    RoomObject* roomObjectPtr;                               //stores a pointer to a room object
    vector<Item*> items;                                     //stores a vector of pointers to items present in the room
    
    //Room description
    string description;                                      //stores room description generated based on initialized pointers
    
public:
    //Constructor
    /* Initializes room data to null values */
    Room(int row = 0, int col = 0, unsigned char wall = 0);
    
    //Destructor
    /* Sets Monster and RoomObject pointers to NULL, clears Items vector */
    ~Room();
    
    //Mutators
    /* Sets room's row and col coordinates */
    void setCoordinates (int r, int c)
    {
        coordinates.row = r;
        coordinates.col = c;
    }
    
    /* Sets room's wall data stored as an unsigned char */
    void setWalls(unsigned char w)
    {
        walls = w;
    };
    
    /* Initializes MonsterPtr with an address of a Monster object */
    void setMonsterPtr(Monster* mptr = nullptr)
    {
        monsterPtr = mptr;
    }
    
    /* Initializes RoomObjectPtr with an address of a RoomObject object */
    void setRoomObjectPtr(RoomObject* roptr = nullptr)
    {
        roomObjectPtr = roptr;
    }
    
    /* Initializes a vector of Item pointers with an address of a single Item object */
    void setItem(Item* iptr = nullptr)    // nullptr is a C++ 11 feature
    {
        if (iptr != nullptr)  // CHANGE : !iptr   DOES NOT WORK
        {
            items.push_back(iptr);
        }
    }
    
    /* Displays a room description generated based on intialized pointers */
    void setDescription()
    {
        if (getMonsterPtr())
        {
            description = "In this room you find a(n) " + getMonsterPtr()->getName() + "\n" + getMonsterPtr()->getDescription();
        }
        else if (getRoomObjectPtr())
        {
            description = "In this room you find a(n) " + getRoomObjectPtr()->getName() + "\n" + getRoomObjectPtr()->getDescription();
        }
        else if (!items.empty())
        {
            description = "In this room you find a(n) ";
            for (int i = 0; i < items.size(); i++)
            {
                Item* temp = items[i];
                if (temp != nullptr)
                {
                    description += temp->name() + " ";
                    description += temp->description();
                }
            }
        }
        else
        {
            description = "This room is empty";
        }
    }
    
    //Accessors
    /* Returns a reference to a struct with room coordinates */
    const RoomCoordinates& getRoomCoordinates() const
    {
        return coordinates;
    }
    /* Returns an unsigned char storing wall data */
    const unsigned char getWalls() const
    {
        return walls;
    }
    /* Returns a pointer to a monster if monster is present in the room
     Returns nullptr if no monsters are present in the room */
    Monster* getMonsterPtr() const
    {
        return monsterPtr;
    }
    /* Returns a pointer to a room object if a room object is present in the room
     Returns nullptr if no room objects are present in the room */
    RoomObject* getRoomObjectPtr() const
    {
        return roomObjectPtr;
    }
    /* Returns a vector of item pointers if at least one item object is present in the room
     Returns an empty vector if no item objects are present in the room */
    vector<Item*> getItems() const
    {
        return items;
    }
    
    /* Removes an item from the vector of items. Returns pointer to the removed item.
     Returns nullptr if item vector is empty. */
    Item* removeItem(string anItem);
    
    /* Returns a pointer to the current room */
    Room& getRoom()
    {
        return *this;
    }
    /* Returns a string with a room description */
    string getDescription()
    {
        setDescription();
        
        return description;
    }
    
    //Directional movement functions
    /* Returns true if movement north is possible */
    bool checkNorth() const;
    /* Returns true if movement south is possible */
    bool checkSouth() const;
    /* Returns true if movement east is possible */
    bool checkEast() const;
    /* Returns true if movement west is possible */
    bool checkWest() const;
    /* Prints room walls */
    void print(bool westSet) const;
    
    //Item Transfer Functions
    /* Searches Item vector for a specific item. Returns true if the item is found.*/
    bool contains(string s);
    
    //Overloaded Operator<<
    /* Prints room contents */
    friend ostream& operator<<(ostream& strm, const Room& room);
};

#endif


