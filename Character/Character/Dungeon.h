/*
 
 Specification file for the Dungeon class.
 
 The Dungeon class is implemented as a dynamically allocated 2D array (matrix) of Room objects.
 The matrix has dimensions of 10 x 10 units and it is arranged as a labyrinth with walls determining the
 direction of movement of the player.
 Dungeon's layout:
 
 
                                                        0 1 2 3 4 5 6 7 8 9
                                                        _ _ _ _ _ _ _ _ _ _
                                                     0 |   |   |T |   |   |
                                                     1 | | | | | | | | | | |
                                                     2 | | | | | | | | | | |
                                                     3 | |G _|_ _ _ _|_ _| |
                                                     4 |_ _           G _ _|
                                                     5 |   | |  _ _  | |   |
                                                     6 | | | | |   | | | | |
                                                     7 | | | | |   | | | | |
                                                     8 | |G _| |   | |_ _| |
                                                     9 |_ _ _ _ _ _ _ _ _ _|
 
 
 T - room with the treasure
 G - room with a gem
 
 Implementation Details:
 
 Data:
 dungeonPtr - pointer to the dynamically allocated 2D matrix of Room objects
 rows - number of rows in the matrix
 cols - number of columns in the matrix
 int numPopulatedRooms - number of rooms populated with data
 monsters - vector of pointers to all monsters in the dungeon
 item - vector of pointers to all items in the dungeon
 roomObjects - vector of pointers to all room objects in the dungeon
 ruby, sapphire, emerald - pointers to gems (items with special room designations)
 treasure - pointer to the treasure that wins the game (item with special room designation)
 
 Functions:
 alloc - allocates memory for the matrix
 release - releases memory used by the matrix
 addRoom - sets room data for a new room
 Constructor - initializes rows, cols and numPopulatedRooms, calls alloc, addRoomContents and addRoom functions
 Destructor  - calls release function to free memory used by the matrix
 printMap - prints the layout of the dungeon with the character's current location
 Overloaded operator[][] - returns a reference to a Room located at row and col coordinates
 Overloaded operator<< - prints room contents
 
 */

#ifndef Dungeon_h
#define Dungeon_h

#include <iostream>
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
    
    //Room Contents Data
    vector<Monster*> monsters;                      //vector of pointers to all monsters in the dungeon
    vector<Item*> items;                            //vector of pointers to all items in the dungeon
    vector<RoomObject*> roomObjects;                //vector of pointers to all room objects in the dungeon
    Item* ruby;                                     //pointer to a ruby that must be alocated in a specific room
    Item* sapphire;                                 //pointer to a sapphire that must be alocated in a specific room
    Item* emerald;                                  //pointer to a emerald that must be alocated in a specific room
    RoomObject* treasure;                           //pointer to a treasure that must be allocated in a specific room
    Monster* dragonBoss;                            //pointer to a dragonBoss that must be allocated in a specific room
    
    //Memory Management Functions
    /* Allocates memory for the dungeon matrix of size row x cols */
    void alloc() throw (bad_alloc);
    /* Releases memory used by the dungeon matrix */
    void release();
    
    //Mnutators
    /* Sets room data for Room objects allocated via alloc function */
    void addRoom(int r, int c, unsigned char w);
    /* Initializes vectors with all room contents in the dungeon (monsters, items, room objects) with data */
    bool addRoomContents() throw(bad_alloc);
    
    /* Prints room contents of a room at row, col. Returns a char representing specific room contents. */
    char _printContents(int r, int c);
    
public:
    //Constructor
    /* Allocates memory for the dungeon matrix and intializes each room with data */
    Dungeon(int r, int c) throw(AdventureErrors::FileOpenError);
    
    //Destructor
    /* Deallocates memory used by the dungeon matrix */
    ~Dungeon();
    
    //Accessors
    /* Prints dungeon map and character's position inside the dungeon */
    void printMap(int characterRow, int characterCol) const;
    /* Prints the contents of 4 rooms  adjacent to the room at x, y */
    void printAdjacentRooms(int characterRow, int characterCol) throw (AdventureErrors::BoundaryError);
    /* Prints dungeon's walls */
    void printWalls() const;
    
    /* Returns a reference to a room at coordinates represented by row and col */
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

