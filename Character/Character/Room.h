/*
 
 Specification file for the Room class.
 
 A Room is one Dungeon (matrix) unit that can be entered, traversed and exited by the player according the Dungeon layout.
  
 */

#ifndef Room_h
#define Room_h

#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <iomanip>
#include "Monster.h"
#include "RoomObject.h"
#include "Item.h"
using namespace std;

struct RoomCoordinates
{
    int row;
    int col;
};

class Room
{
private:
    //Room coordinates & wall data
    RoomCoordinates coordinates;                             //Room ID represented by row and col coordinates
    unsigned char walls;                                     //stores wall positions in the last nibble of the 8-bit unsigned char
    
    //Pointers to monster, room object and list of items
    Monster* monsterPtr;                                     //stores a pointer to a monster
    RoomObject* roomObjectPtr;                               //stores a pointer to a room object
    list<Item*> items;                                       //stores a list of pointers to items present in the room
    
public:
    //Constructor
    /* Initializes room data to null values */
    Room(int row = 0, int col = 0, unsigned char wall = 0);
    
    //Destructor
    /* Sets Monster and RoomObject pointers to NULL, clears Items list */
    ~Room();
    
    //Mutators
    /* Sets room's row and col coordinates */
    void setCoordinates (int r, int c);
    
    /* Sets room's wall data stored as an unsigned char */
    void setWalls(unsigned char w);
    
    /* Initializes MonsterPtr with an address of a Monster object */
    void setMonsterPtr(Monster* mptr = nullptr);
    
    /* Initializes RoomObjectPtr with an address of a RoomObject object */
    void setRoomObjectPtr(RoomObject* roptr = nullptr);
    
    /* Adds an Item pointer to the list of items */
    void setItem(Item* iptr = nullptr);
    
    /* Removes a monster from the room by deleting the monster object and setting MonsterPtr to NULL */
    void removeMonster();
    
    /* Removes an item from the list of items. Returns pointer to the removed item.*/
    Item* removeItem(string anItem);
    
    //Accessors
    /* Returns row coordinate */
    int getRow() const;
    
    /* Returns col coordinate */
    int getCol() const;
    
    /* Returns a reference to a struct with room coordinates */
    const RoomCoordinates& getRoomCoordinates() const;
    
    /* Returns an unsigned char storing wall data */
    const unsigned char getWalls() const;
    
    /* Returns a pointer to a monster if monster is present in the room. Returns nullptr otherwise. */
    Monster* getMonsterPtr() const;
    
    /* Returns a pointer to a room object if a room object is present in the room. Returns nullptr otherwise. */
    RoomObject* getRoomObjectPtr() const;
    
    /* Returns a list of item pointers if at least one item object is present in the room */
    list<Item*> getItems() const;
    
    /* Returns a pointer to the current room */
    Room& getRoom();
    
    //Directional movement functions
    /* Returns true if movement north is possible */
    bool checkNorth() const;
    /* Returns true if movement south is possible */
    bool checkSouth() const;
    /* Returns true if movement east is possible */
    bool checkEast() const;
    /* Returns true if movement west is possible */
    bool checkWest() const;
    
    //Item Transfer Functions
    /* Searches Item list for a specific item. Returns true if the item is found.*/
    bool contains(string s);
    
    //Overloaded Operator<<
    /* Prints room contents/description */
    friend ostream& operator<<(ostream& strm, const Room& room);
};

#endif


