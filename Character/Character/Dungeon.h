/*
 
 Specification file for the Dungeon class.
 
 The Dungeon class is implemented as a dynamically allocated 2D array (matrix) of Room objects.
 The matrix has dimensions of 10 x 10 units and it is arranged as a labyrinth with walls limiting
 character's directional movement. The objective of the game is to get to the room with the
 treasure (0, 4) and collect the three gems (ruby, sapphire, and emerald) neccessary to activate
 the trasure as well as get the kill scroll necessary to kill the dragon boss guarding the treasure.
 Dungeon's layout:
 
 
                                                        0 1 2 3 4 5 6 7 8 9
                                                        _ _ _ _ _ _ _ _ _ _
                                                     0 |   |   |T  |   |   |
                                                     1 | | | | | | | | | | |
                                                     2 | | | | | | |K| | | |
                                                     3 | |G _|_ _ _ _|_ _| |
                                                     4 |_ _           G _ _|
                                                     5 |   | |  _ _  | |   |
                                                     6 | | | | |   | | | | |
                                                     7 | | | | |   | | | | |
                                                     8 | |G _| |   | |_ _| |
                                                     9 |_ _ _ _ _ _ _ _ _ _|
 
 
 T - room with the treasure
 G - room with a gem
 K - room with a kill scroll
 */

#ifndef Dungeon_h
#define Dungeon_h

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <string>
#include <new>
#include "Room.h"
#include "Exceptions.h"
#include "Generation.h"
using namespace std;

class Dungeon
{
private:
    //Dungeon data
    Room** dungeonPtr;                              //pointer to the dungeon
    int rows;                                       //row count
    int cols;                                       //column count
    int numPopulatedRooms;                          //number of populated rooms
 
    //Memory Management Functions
    /* Allocates memory for the dungeon matrix of size row x cols */
    void alloc() throw (bad_alloc);
    
    /* Releases memory used by the dungeon matrix */
    void release();
    
    //Mutators
    /* Sets wall data data for Room objects allocated via alloc function */
    void addRoom(int r, int c, unsigned char w);
    
    /* Initializes monster, room object and item data for Room objects allocated via alloc function */
    void putThingsIntoDungeon(const int &numMonsters, const int &numPots, const int &numEquipment, const int &numRoomObjs);
    
    //Accessors
    /* Prints room contents of a room at row & col. Returns a char representing specific room contents. */
    char _printContents(int r, int c);
    
    /*  Prints a map with locations of essentials necessary to win the game (treasure, gems & kill scroll) */
    void _printBasicMap(int characterRow, int characterCol) const;
    
    /*  Prints a map with monsters only */
    void _printMonsterMap(int characterRow, int characterCol) const;
    
    /*  Prints a map with room objects only */
    void _printRoomObjectMap(int characterRow, int characterCol) const;
    
    /*  Prints a map with items only */
    void _printItemsMap(int characterRow, int characterCol) const;
    
    /*  Prints a map with all room objects, items and monsters located in the dungeon */
    void _printAllMap(int characterRow, int characterCol) const;
    
public:
    /* enum flag representing map version passed to the printMap() function */
    enum MapType {BASIC, MONSTER, ROOMOBJECT, ITEM, ALL};
    
    //Constructor
    /* Allocates memory for the dungeon matrix and intializes each room with data */
    Dungeon(int r, int c) throw(AdventureErrors::FileOpenError);
    
    //Destructor
    /* Deallocates memory used by the dungeon matrix */
    ~Dungeon();
    
    //Accessors
    /* Prints a version of dungeon map given an enum flag passed to it and displays character's position inside the dungeon */
    void printMap(int characterRow, int characterCol, MapType version) const;
    
    /* Prints the contents of 4 rooms adjacent to the room at x, y */
    void printAdjacentRooms(int characterRow, int characterCol) throw (AdventureErrors::BoundaryError);
    
    /* Returns a reference to a room at coordinates row, col */
    Room& getRoom(const int row, const int col)
    {
        return dungeonPtr[row][col];
    }
    
    //Overloaded Operator<<
    /* Prints dungeon contents */
    friend ostream& operator<<(ostream& strm, const Dungeon& dungeon);
    
    //Overloaded Operator[][]
    /* Returns a reference to a room at coordinates represented by row and col */
    class Proxy
    {
    private:
        Room* RoomPtr;
    public:
        Proxy(Room* ptr) : RoomPtr(ptr) {}
        Room&  operator[](int index)
        {
            return RoomPtr[index];
        }
    };
    Proxy operator[](int index)
    {
        return Proxy(dungeonPtr[index]);
    }
};

#endif

