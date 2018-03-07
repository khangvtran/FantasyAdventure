/*
 
 Implementation file for the Dungeon class.
 
 */

#include "Dungeon.h"

/********************************************************************************************
 alloc
 Allocates memory for a 2D matix of Room objects representing the Dungeon.
 *******************************************************************************************/
void Dungeon::alloc() throw(bad_alloc)
{
    try
    {
        dungeonPtr = new Room*[rows];
        for (int i = 0; i < rows; i++)
        {
            dungeonPtr[i] = new Room[cols];
        }
    }
    catch (bad_alloc)
    {
        cout << "Insufficient memory." << endl;
    }
}
/********************************************************************************************
 release
 Frees the heap space used by the matrix.
 *******************************************************************************************/
void Dungeon::release()
{
    for (int i = 0; i < rows; i++)
    {
        delete [] dungeonPtr[i];
    }
    delete [] dungeonPtr;
}

/********************************************************************************************
 Constructor
 Initializes row and column count and number of populated rooms. Allocates memory for the dungeon.
 Initializes vectors of all room contents (monsters, items, room objects) and sets room data
 for each room.
 *******************************************************************************************/
Dungeon::Dungeon(int r, int c) throw(AdventureErrors::FileOpenError) : rows(r), cols(c), numPopulatedRooms(0)
{
    //Allocate memory for the dungeon
    alloc();
    
    //Set room coordinates and wall data
    const char fileName[] = "/Users/Agnieszka Rynkiewicz/Desktop/Computer Science/1.7 C++/1.1 C++ Courses/1.3 Advanced C++/1.0 Group Project/3.0 Code/walls.bin";
    
    //Open file with room data
    fstream file;
    try
    {
        file.open(fileName, ios::in | ios::binary);
        if (!file)
        {
            throw AdventureErrors::FileOpenError(fileName);
        }
    }
    catch (const AdventureErrors::FileOpenError& e)
    {
        string newFile;
        cout << e.what() << endl;
        file.clear();
        cout << "Enter another file: ";
        getline(cin, newFile);
        file.open(newFile.c_str());
        if (!file)
        {
            cout << "File Open Error" << endl;
            exit(EXIT_FAILURE);
        }
    }
    
    struct Room
    {
        int row;
        int col;
        unsigned char wall;
    };
    Room newRoom;                   //temp struct used to store data read from file
    
    //Take the first read
    file.read(reinterpret_cast<char*>(&newRoom), sizeof(Room));
    //cout << "ROW:  " << newRoom.row << " " << "COL:  " << newRoom.col << " WALL: " << static_cast<int>(newRoom.wall) << endl;

    
    //Read room data until EOF
    while (!file.eof())
    {
        //Add a new room
        addRoom(newRoom.row, newRoom.col, newRoom.wall);
        
       
        //Take a subsequent read to check for EOF bit
        file.read(reinterpret_cast<char*>(&newRoom), sizeof(Room));
        //cout << "ROW:  " << newRoom.row << " " << "COL:  " << newRoom.col << " WALL: " << static_cast<int>(newRoom.wall) << endl;
    }
    
    putthingsintodungeon(18, 15, 20, 20); // ADDED THIS LINE
    //printMap(0,0); // ADDED THIS LINE TO DEBUG PRINT MAP
    
    //Close file
    file.close();
}

void Dungeon::putthingsintodungeon(const int &numMonsters, const int &numPots, const int &numEquipment, const int &numRoomObjs)
{
    bool roomData[10][10] = {false};
    Generation spawner;
    
    roomData[0][4] = true;
    dungeonPtr[0][4].setMonsterPtr(spawner.generateMonster(spawner.DRAGONBOSS)); // generates dragonboss at 0,4
    dungeonPtr[0][4].setRoomObjectPtr(spawner.generateRoomObj(spawner.TREASURE)); // generates treasure at 0,4
    
    roomData[2][6] = true;
    dungeonPtr[2][6].setItem(spawner.generateItem(spawner.KILLSCROLL)); // generates KillScroll at 2, 6
    
    roomData[3][1] = true;
    dungeonPtr[3][1].setItem(spawner.generateItem(spawner.RUBY)); // generates Ruby at 3,1
    
    roomData[4][7] = true;
    dungeonPtr[4][7].setItem(spawner.generateItem(spawner.SAPPHIRE)); // generates Sapphire at 4,7
    
    roomData[8][1] = true;
    dungeonPtr[8][1].setItem(spawner.generateItem(spawner.EMERALD)); // generates Emerald at 8,1

    int monsterCount = 0;
    int potCount = 0;
    int equipmentCount = 0;
    int roomObjCount = 0;
    int rowNum, colNum;
    do
    {
        rowNum = rand() % rows;
        colNum = rand() % cols;
        
        if(!roomData[rowNum][colNum]) // if room is empty
        {
            if(monsterCount != numMonsters)
            {
                dungeonPtr[rowNum][colNum].setMonsterPtr(spawner.generateMonster((Generation::MONSTERS)(rand() % (spawner.monsterContainer.size()-1)))); // put this into the room
                cout << "generated" << dungeonPtr[rowNum][colNum].getMonsterPtr()->getName() << endl;
                monsterCount++;
            }
            else if(potCount != numPots)
            {
                dungeonPtr[rowNum][colNum].setItem(spawner.generateItem((Generation::ITEMS)(rand() % 5))); // put this into the room
                potCount++;
                cout << "generated" << (*(dungeonPtr[rowNum][colNum].getItems().begin()))->name() << endl;
            }
            else if(equipmentCount != numEquipment)
            {
                // rand() % ((spawner.itemContainer.size() - (6+3)) +6) generates a random number between 6 and 25 (which is the first of equipment and last of equipment)
                dungeonPtr[rowNum][colNum].setItem(spawner.generateItem((Generation::ITEMS)(rand() % (spawner.itemContainer.size() - (6+3)) +6))); // put this into the room
                cout << "generated" << (*(dungeonPtr[rowNum][colNum].getItems().begin()))->name() << endl;
                equipmentCount++;
            }
            else if(roomObjCount != numRoomObjs)
            {
                dungeonPtr[rowNum][colNum].setRoomObjectPtr(spawner.generateRoomObj((Generation::ROOMOBJ)(rand() % (spawner.roomObjContainer.size()-1)))); // put this into the room
                cout << "generated" << dungeonPtr[rowNum][colNum].getRoomObjectPtr()->getName() << endl;
                roomObjCount++;
            }
            roomData[rowNum][colNum] = true;
        }
    } while(monsterCount != numMonsters || potCount != numPots || equipmentCount != numEquipment || roomObjCount != numRoomObjs);
    
    cout << "should have " << numMonsters << " monsters and have " << monsterCount << endl;
    cout << "should have " << numPots << " pots and have " << potCount << endl;
    cout << "should have " << numEquipment << " equipment and have " << equipmentCount << endl;
    cout << "should have " << numRoomObjs << " roomobjs and have " << roomObjCount << endl;
    
}
/********************************************************************************************
 addRoom
 Sets room data for a new room.
 *******************************************************************************************/
void Dungeon::addRoom(int r, int c, unsigned char w)
{
    //Set room coordinates and wall data
    dungeonPtr[r][c].setCoordinates(r, c);
    dungeonPtr[r][c].setWalls(w);
    
    //Increment number of populated rooms
    numPopulatedRooms++;
}

/********************************************************************************************
 Destructor
 Calls release function to deallocate memory used by the dungeon matrix.
 *******************************************************************************************/
Dungeon::~Dungeon()
{
    //Release memory used by dungeon matrix
    release();
}

/********************************************************************************************
 printMap
 Prints the layout of the dungeon with character's current position marked with a star "*".
 A different version of the map is displayed given the enum value passed to it:
 version = 0 displays essentials only (treasure, gems & kill scroll)
 version = 1 displays monsters only
 version = 2 displays room objects only
 version = 3 displays items only
 *******************************************************************************************/
void Dungeon::printMap(int characterRow, int characterCol, MapType version) const
{
    if (version == BASIC)
    {
        _printBasicMap(characterRow, characterCol);
    }
    else if (version == MONSTER)
    {
        _printMonsterMap(characterRow, characterCol);
    }
    else if (version == ROOMOBJECT)
    {
        _printRoomObjectMap(characterRow, characterCol);
    }
    else if (version == ITEM)
    {
        _printItemsMap(characterRow, characterCol);
    }
    else if (version == ALL)
    {
        _printAllMap(characterRow, characterCol);
    }
    else
    {
        cout << "Not a valid option!" << endl;
    }
}

/********************************************************************************************
 _printBasicMap
 Prints a map with locations of essentials necessary to win the game (treasure, gems & kill scroll).
 *******************************************************************************************/
void Dungeon::_printBasicMap(int characterRow, int characterCol) const
{
    cout << "\n\n\n" << endl;
    cout << setw(98) << "               ~~***   BASIC MAP   ***~~               \n" << endl;
    cout << setw(86) << " 0  1  2  3  4  5  6  7  8  9  " << endl;
    
    //Check for room object
    for (int r = 0; r < 10; r++)
    {
        cout << right << setw(55) << r;
        for (int c = 0; c < 10; c++)
        {
            //Print Character's location
            if (r == characterRow && c == characterCol)
            {
                cout << " * ";
            }
            //Print treasure's location
            else if (dungeonPtr[r][c].getRoomObjectPtr())
            {
                RoomObject* temp = dungeonPtr[r][c].getRoomObjectPtr();
                Treasure* tPtr = dynamic_cast<Treasure*>(temp);
                if (tPtr)
                {
                    cout << " T ";
                }
                else
                {
                    cout << "   ";
                }
            }
            //Print gem's location and kill scroll's location
            else if (!dungeonPtr[r][c].getItems().empty())
            {
                vector<Item*> temp = dungeonPtr[r][c].getItems();
                PortalGem* gPtr = dynamic_cast<PortalGem*>(temp[0]);
                KillScroll* kPtr = dynamic_cast<KillScroll*>(temp[0]);
                if (gPtr)
                {
                    cout << " G ";
                }
                else if (kPtr)
                {
                    cout << " K ";
                }
                else
                {
                    cout << "   ";
                }
            }
            else
            {
                cout << "   ";
            }
        }
        cout << left << r;
        cout << "\n";  //Remove this newline to make the map more compact
        if (r < 9)
        {
            cout << endl;
        }
    }
    cout << right << setw(86) << " 0  1  2  3  4  5  6  7  8  9  " << endl;
    cout << left << "\n" << endl;
    cout << right << setw(55) << " " << left << "LEGEND: " << endl;
    cout << right << setw(55) << " " << left << "* - You are here (row " << characterRow << ", col " << characterCol << ")" << endl;
    cout << right << setw(55) << " " << left << "T - Treasure " << endl;
    cout << right << setw(55) << " " << left << "K - Kill Scroll " << endl;
    cout << right << setw(55) << " " << left << "G - Gem (Ruby, Sapphire, Emerald)\n" << endl;
    cout << setw(96) << right << "              ~~***   ***   ***~~               \n" << endl;
    
    cout << "\n\n\n" << endl;
    
}

/********************************************************************************************
 _printMonsterMap
 Prints a map with monsters only.
 *******************************************************************************************/
void Dungeon::_printMonsterMap(int characterRow, int characterCol) const
{
    cout << "\n\n\n" << endl;
    cout << setw(100) << "               ~~***   MONSTER MAP   ***~~               \n" << endl;
    cout << setw(86) << " 0  1  2  3  4  5  6  7  8  9  " << endl;
    
    //Check for room object
    for (int r = 0; r < 10; r++)
    {
        cout << right << setw(55) << r;
        for (int c = 0; c < 10; c++)
        {
            //Print Character's location
            if (r == characterRow && c == characterCol)
            {
                cout << " * ";
            }
            //Print Monster's location
            else if (dungeonPtr[r][c].getMonsterPtr())
            {
               cout << " M ";
            }
            else
            {
                cout << "   ";
            }
        }
        cout << left << r;
        cout << "\n";  //Remove this newline to make the map more compact
        if (r < 9)
        {
            cout << endl;
        }
    }
    cout << right << setw(86) << " 0  1  2  3  4  5  6  7  8  9  " << endl;
    cout << left << "\n" << endl;
    cout << right << setw(55) << " " << left << "LEGEND: " << endl;
    cout << right << setw(55) << " " << left << "* - You are here (row " << characterRow << ", col " << characterCol << ")" << endl;
    cout << right << setw(55) << " " << left << "M - Monster " << endl;
    cout << setw(96) << right << "              ~~***   ***   ***~~               \n" << endl;
    
    cout << "\n\n\n" << endl;
    
}

/********************************************************************************************
 _printRoomObjectMap
 Prints a map with room objects only.
 *******************************************************************************************/
void Dungeon::_printRoomObjectMap(int characterRow, int characterCol) const
{
    cout << "\n\n\n" << endl;
    cout << setw(102) << "               ~~***   ROOM OBJECT MAP   ***~~               \n" << endl;
    cout << setw(86) << " 0  1  2  3  4  5  6  7  8  9  " << endl;
    
    //Check for room object
    for (int r = 0; r < 10; r++)
    {
        cout << right << setw(55) << r;
        for (int c = 0; c < 10; c++)
        {
            //Print Character's location
            if (r == characterRow && c == characterCol)
            {
                cout << " * ";
            }
            //Print each Item's location
            else if (dungeonPtr[r][c].getRoomObjectPtr())
            {
                RoomObject* temp = dungeonPtr[r][c].getRoomObjectPtr();
                Book* bPtr = dynamic_cast<Book*>(temp);
                Flare* fPtr = dynamic_cast<Flare*>(temp);
                Map* mPtr = dynamic_cast<Map*>(temp);
                Fountain* ftPtr = dynamic_cast<Fountain*>(temp);
                
                //Book
                if (bPtr)
                {
                    cout << " B ";
                }
                //Flare
                else if (fPtr)
                {
                    cout << " F ";
                }
                //Map
                else if (mPtr)
                {
                    cout << " M ";
                }
                //Fountain
                else if (ftPtr)
                {
                    cout << " R ";
                }
                else
                {
                    cout << "   ";
                }
            }
            else
            {
                cout << "   ";
            }
        }
        cout << left << r;
        cout << "\n";  //Remove this newline to make the map more compact
        if (r < 9)
        {
            cout << endl;
        }
    }
    cout << right << setw(86) << " 0  1  2  3  4  5  6  7  8  9  " << endl;
    cout << left << "\n" << endl;
    cout << right << setw(55) << " " << left << "LEGEND: " << endl;
    cout << right << setw(55) << " " << left << "* - You are here (row " << characterRow << ", col " << characterCol << ")" << endl;
    cout << right << setw(55) << " " << left << "B - Book " << endl;
    cout << right << setw(55) << " " << left << "F - Flare " << endl;
    cout << right << setw(55) << " " << left << "M - Map " << endl;
    cout << right << setw(55) << " " << left << "R - Fountain " << endl;
    cout << setw(96) << right << "              ~~***   ***   ***~~               \n" << endl;
    
    cout << "\n\n\n" << endl;
    
}

/********************************************************************************************
 _printItemsMap
 Prints a map with items only.
 *******************************************************************************************/
void Dungeon::_printItemsMap(int characterRow, int characterCol) const
{
    cout << "\n\n\n" << endl;
    cout << setw(98) << "               ~~***   ITEMS MAP   ***~~               \n" << endl;
    cout << setw(86) << " 0  1  2  3  4  5  6  7  8  9  " << endl;
    
    //Check for room object
    for (int r = 0; r < 10; r++)
    {
        cout << right << setw(55) << r;
        for (int c = 0; c < 10; c++)
        {
            //Print Character's location
            if (r == characterRow && c == characterCol)
            {
                cout << " * ";
            }
            //Print Monster's location
            else if (!dungeonPtr[r][c].getItems().empty())
            {
                vector<Item*> temp = dungeonPtr[r][c].getItems();
                PortalGem* gPtr = dynamic_cast<PortalGem*>(temp[0]);
                KillScroll* kPtr = dynamic_cast<KillScroll*>(temp[0]);
                Equipment* ePtr = dynamic_cast<Equipment*>(temp[0]);
                if (gPtr)
                {
                    cout << " G ";
                }
                else if (kPtr)
                {
                    cout << " K ";
                }
                else if (ePtr)
                {
                    cout << " E ";
                }
                else
                {
                    cout << "   ";
                }
            }
            else
            {
                cout << "   ";
            }
        }
        cout << left << r;
        cout << "\n";  //Remove this newline to make the map more compact
        if (r < 9)
        {
            cout << endl;
        }
    }
    cout << right << setw(86) << " 0  1  2  3  4  5  6  7  8  9  " << endl;
    cout << left << "\n" << endl;
    cout << right << setw(55) << " " << left << "LEGEND: " << endl;
    cout << right << setw(55) << " " << left << "* - You are here (row " << characterRow << ", col " << characterCol << ")" << endl;
    cout << right << setw(55) << " " << left << "G - Gem (Ruby, Sapphire, Emerald)" << endl;
    cout << right << setw(55) << " " << left << "K - Kill Scroll " << endl;
    cout << right << setw(55) << " " << left << "E - Equipment " << endl;
    cout << setw(96) << right << "              ~~***   ***   ***~~               \n" << endl;
    
    cout << "\n\n\n" << endl;
    
}

/********************************************************************************************
 _printAllMap
 Prints a map with all room objects, items and monsters in the dungeon.
 *******************************************************************************************/
void Dungeon::_printAllMap(int characterRow, int characterCol) const
{
    cout << "\n\n\n" << endl;
    cout << setw(100) << "               ~~***   GENERAL MAP   ***~~               \n" << endl;
    cout << setw(86) << " 0  1  2  3  4  5  6  7  8  9  " << endl;
    
    //Check for room object
    for (int r = 0; r < 10; r++)
    {
        cout << right << setw(55) << r;
        for (int c = 0; c < 10; c++)
        {
            //Print Character's location
            if (r == characterRow && c == characterCol)
            {
                cout << " * ";
            }
            //Print all Room Object's locations
            else if (dungeonPtr[r][c].getRoomObjectPtr())
            {
                RoomObject* temp = dungeonPtr[r][c].getRoomObjectPtr();
                Treasure* tPtr = dynamic_cast<Treasure*>(temp);
                Book* bPtr = dynamic_cast<Book*>(temp);
                Flare* fPtr = dynamic_cast<Flare*>(temp);
                Map* mPtr = dynamic_cast<Map*>(temp);
                Fountain* ftPtr = dynamic_cast<Fountain*>(temp);
                
                //Treasure
                if (tPtr)
                {
                    cout << " T ";
                }
                //Book
                else if (bPtr)
                {
                    cout << " B ";
                }
                //Flare
                else if (fPtr)
                {
                    cout << " F ";
                }
                //Map
                else if (mPtr)
                {
                    cout << " D ";
                }
                //Fountain
                else if (ftPtr)
                {
                    cout << " R ";
                }
                else
                {
                    cout << "   ";
                }
            }
            //Print all Items' locations
            else if (!dungeonPtr[r][c].getItems().empty())
            {
                vector<Item*> temp = dungeonPtr[r][c].getItems();
                PortalGem* gPtr = dynamic_cast<PortalGem*>(temp[0]);
                KillScroll* kPtr = dynamic_cast<KillScroll*>(temp[0]);
                Equipment* ePtr = dynamic_cast<Equipment*>(temp[0]);
                Potion* pPtr = dynamic_cast<Potion*>(temp[0]);
                
                //Gem
                if (gPtr)
                {
                    cout << " G ";
                }
                //KillScroll
                else if (kPtr)
                {
                    cout << " K ";
                }
                //Equipment
                else if (ePtr)
                {
                    cout << " E ";
                }
                //Potion
                else if (pPtr)
                {
                    cout << " P ";
                }
                else
                {
                    cout << "   ";
                }
            }
            //Print all Monsters' locations
            else if (dungeonPtr[r][c].getMonsterPtr())
            {
                cout << " M ";
            }
            else
            {
                cout << "   ";
            }
        }
        cout << left << r;
        cout << "\n";  //Remove this newline to make the map more compact
        if (r < 9)
        {
            cout << endl;
        }
    }
    cout << right << setw(86) << " 0  1  2  3  4  5  6  7  8  9  " << endl;
    cout << left << "\n" << endl;
    cout << right << setw(55) << " " << left << "LEGEND: " << endl;
    cout << right << setw(55) << " " << left << "* - You are here (row " << characterRow << ", col " << characterCol << ")" << endl;
    cout << right << setw(55) << " " << left << "T - Treasure " << endl;
    cout << right << setw(55) << " " << left << "B - Book " << endl;
    cout << right << setw(55) << " " << left << "F - Flare " << endl;
    cout << right << setw(55) << " " << left << "D - Map " << endl;
    cout << right << setw(55) << " " << left << "R - Fountain " << endl;
    cout << right << setw(55) << " " << left << "G - Gem (Ruby, Sapphire, Emerald)" << endl;
    cout << right << setw(55) << " " << left << "K - Kill Scroll " << endl;
    cout << right << setw(55) << " " << left << "E - Equipment " << endl;
    cout << right << setw(55) << " " << left << "P - Potion " << endl;
    cout << right << setw(55) << " " << left << "M - Monster " << endl;
    cout << setw(96) << right << "              ~~***   ***   ***~~               \n" << endl;
    
    cout << "\n\n\n" << endl;
    
    
}


/********************************************************************************************
 printAdjacentRooms
 Takes room coordinates as arguments and prints room contents of 4 adjacent rooms.
 *******************************************************************************************/
void Dungeon::printAdjacentRooms(int characterRow, int characterCol) throw (AdventureErrors::BoundaryError)
{
    //Stores pointer to a dynamic array of room contents returned by the _printContents function
    char roomContents[10];
    int count = 0;
    
    //Check for dungeon boundaries
    try
    {
        if (characterRow < 0 || characterRow > (rows - 1) || characterCol < 0 || characterCol > (cols - 1))
        {
            throw AdventureErrors::BoundaryError("That's outside the dungeon's boundaries");
        }
    }
    catch (const AdventureErrors::BoundaryError& e)
    {
        cout << e.what() << endl;
    }
    
    cout << "\n\n\n" << endl;
    cout << setw(102) << "               ~~***   4 ADJACENT ROOMS   ***~~               \n" << endl;
    cout << setw(86) << " 0  1  2  3  4  5  6  7  8  9  " << endl;
    
    //Check for room object
    for (int r = 0; r < 10; r++)
    {
        cout << right << setw(55) << r;
        for (int c = 0; c < 10; c++)
        {
            //Print Room to the NORTH
            if (r == characterRow - 1 && c == characterCol)
            {
                roomContents[count] = _printContents(r, c);
                count++;
            }
            
            //Print Room to the WEST
            else if (r == characterRow && c == characterCol - 1)
            {
                roomContents[count] =  _printContents(r, c);
                count++;
            }
            //Print Character's location
            else if (r == characterRow && c == characterCol)
            {
                cout << " * ";
            }
            //Print Room to the EAST
            else if (r == characterRow && c == characterCol + 1)
            {
               roomContents[count] = _printContents(r, c);
            count++;
            }
            
            //Print Room to the SOUTH
            else if (r == characterRow + 1 && c == characterCol)
            {
                roomContents[count] = _printContents(r, c);
                count++;
            }
            else
            {
                cout << "   ";
            }
        }
        
        cout << left << r;
        cout << "\n";  //Remove this newline to make the map more compact
        if (r < 9)
        {
            cout << endl;
        }
    }
    cout << right << setw(86) << " 0  1  2  3  4  5  6  7  8  9  " << endl;
    cout << left << "\n\n" << endl;
    
    cout << right << setw(55) << " " << left << "LEGEND: " << endl;
    cout << right << setw(55) << " " << left << "* - You are here (row " << characterRow << ", col " << characterCol << ")" << endl;
    bool bookused = false;
    bool flareUsed = false;
    bool fountainUsed = false;
    bool mapUsed = false;
    bool monsterUsed = false;
    bool equipUsed = false;
    bool potUsed = false;
    
    // if roomContents[i] = _printContents(r,c) and _printContents(r,c) only returns uppercase characters, then why need toUpper?
    for (int i = 0; i < count; i++)
    {
        if (toupper(roomContents[i]) == 'T')
        {
            cout << right << setw(55) << " " << left << "T - Treasure " << endl;
        }
        else if (toupper(roomContents[i]) == 'B' && !bookused)
        {
            cout << right << setw(55) << " " << left << "B - Book " << endl;
            bookused = false;
        }
        else if (toupper(roomContents[i]) == 'F' && !flareUsed)
        {
            cout << right << setw(55) << " " << left << "F - Flare " << endl;
            flareUsed = true;
        }
        else if (toupper(roomContents[i]) == 'R' && !fountainUsed)
        {
            cout << right << setw(55) << " " << left << "R - Fountain " << endl;
            fountainUsed = true;
        }
        else if (toupper(roomContents[i]) == 'D' && !mapUsed)
        {
            cout << right << setw(55) << " " << left << "D - Map " << endl;
            mapUsed = true;
        }
        else if (toupper(roomContents[i]) == 'M' && !monsterUsed)
        {
            cout << right << setw(55) << " " << left << "M - Monster " << endl;
            monsterUsed = true;
        }
        else if (toupper(roomContents[i]) == 'G')
        {
            cout << right << setw(55) << " " << left << "G - Gem (Ruby, Sapphire, Emerald)" << endl;
        }
        else if (toupper(roomContents[i]) == 'Q' && !equipUsed)
        {
            cout << right << setw(55) << " " << left << "Q - Equipment" << endl;
            equipUsed = true;
        }
        else if (toupper(roomContents[i]) == 'P' && !potUsed)
        {
            cout << right << setw(55) << " " << left << "P - Potion" << endl;
            potUsed = true;
        }
    }
    cout << endl;
    cout << setw(96) << right << "              ~~***   ***   ***~~               \n" << endl;
    cout << "\n\n\n" << endl;
    
}

/********************************************************************************************
 Overloaded ostream Operator<<
 Prints data for each room in the dungeon.
 *******************************************************************************************/
ostream& operator<<(ostream& strm, const Dungeon& dungeon)
{
    for (int i = 0; i < dungeon.rows; i++)
    {
        for (int j = 0; j < dungeon.cols; j++)
        {
            strm << dungeon.dungeonPtr[i][j];
        }
    }
    
    return strm;
}

/********************************************************************************************
 _printContents
 Prints room contents of a room at row, col.
 Returns a char representing specific room contents.
 *******************************************************************************************/
char Dungeon::_printContents(int r, int c)
{
    
    //Check for RoomObjects
    if (dungeonPtr[r][c].getRoomObjectPtr())
    {
        RoomObject* temp = dungeonPtr[r][c].getRoomObjectPtr();
        Treasure* tPtr = dynamic_cast<Treasure*>(temp);
        Book* bPtr = dynamic_cast<Book*>(temp);
        Flare* fPtr = dynamic_cast<Flare*>(temp);
        Fountain* ftPtr = dynamic_cast<Fountain*>(temp);
        Map* mPtr = dynamic_cast<Map*>(temp);
        
        if (tPtr)
        {
            cout << " T ";
            return 'T';
        }
        else if (bPtr)
        {
            cout << " B ";
            return 'B';
        }
        else if (fPtr)
        {
            cout << " F ";
            return 'F';
        }
        else if (ftPtr)
        {
            cout << " R ";
            return 'R';
        }
        else if (mPtr)
        {
            cout << " D ";
            return 'P';
        }
    }
    
    //Check for Monsters
    else if (dungeonPtr[r][c].getMonsterPtr())
    {
        cout << " M ";
        return 'M';
    }
    
    //Check for Items
    else if (!dungeonPtr[r][c].getItems().empty())
    {
        vector<Item*> temp = dungeonPtr[r][c].getItems();
        PortalGem* gPtr = dynamic_cast<PortalGem*>(temp[0]);
        Equipment* qPtr = dynamic_cast<Equipment*>(temp[0]);
        Potion* pPtr = dynamic_cast<Potion*>(temp[0]);
        // killscroll??
        if (gPtr)
        {
            cout << " G ";
            return 'G';
        }
        else if (qPtr)
        {
            cout << " Q ";
            return 'Q';
        }
        else
        {
            cout << " P ";
            return 'P';
        }
    }
    else
    {
        cout << "   ";
    }
    
    return '1';
}

/********************************************************************************************
 printWalls
 Prints dungeon's walls.
 *******************************************************************************************/
void Dungeon::printWalls() const
{
    struct Walls
    {
        string id;
        string line1;
        string line2;
        string line3;
    };
    const int SIZE = 4;
    Walls layout[SIZE] = {{"WS", "|   ", "|   ", "|___"},
                           {"W", "|   ", "|   ", "|   "},
                           {"S", "    ", "    ", "____"},
                           {"N", "    ", "    ", "    "}};
    
    bool isSouth = false;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < cols; k++)
            {
                if (!dungeonPtr[i][j].checkWest())
                {
                    if (!dungeonPtr[i][j].checkSouth())
                    {
                        isSouth = true;
                    }
                    cout << layout[i].line1;
                }
            }
            
        }
       
    }
    
    
    
   
}
