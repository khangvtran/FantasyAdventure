/*
 
 Implementation file for the Dungeon class.
 
 */

#include "Dungeon.h"

/********************************************************************************************
 Constructor
 Initializes row and column count and number of populated rooms. Allocates memory for the dungeon.
 Initializes wall data via addRoom function and the remaining room data (monster, room object,
 item) via putThingsIntoDungeon function.
 *******************************************************************************************/
Dungeon::Dungeon(int r, int c) throw(AdventureErrors::FileOpenError) : rows(r), cols(c), numPopulatedRooms(0)
{
    //Allocate memory for the dungeon
    alloc();
    
    //Set room coordinates and wall data for each room
    const char fileName[] = "walls.bin";
    
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
        file.open(newFile.c_str(), ios::in | ios::binary);
        if (!file)
        {
            cout << "File Open Error" << endl;
            exit(EXIT_FAILURE);
        }
    }
    
    //Create a temp struct to store data read from the bin file
    struct Room
    {
        int row;
        int col;
        unsigned char wall;
    };
    Room newRoom;
    
    //Take the first read
    file.read(reinterpret_cast<char*>(&newRoom), sizeof(Room));
    
    //Read room data until EOF
    while (!file.eof())
    {
        //Add a new room
        addRoom(newRoom.row, newRoom.col, newRoom.wall);
        
        //Take a subsequent read to check for EOF bit
        file.read(reinterpret_cast<char*>(&newRoom), sizeof(Room));
    }
    
    //Set monster, room object and item data for each room
    putThingsIntoDungeon(15, 20, 15, 20);
    
    //Close file
    file.close();
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
 addRoom
 Sets room room coordinates and wall data for each room.
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
 printAdjacentRooms
 Takes room coordinates as arguments and prints room contents of 4 adjacent rooms.
 *******************************************************************************************/
void Dungeon::printAdjacentRooms(int characterRow, int characterCol) throw (AdventureErrors::BoundaryError)
{
    //An array of chars representing room contents returned by the _printContents function
    char roomContents[10];
    int count = 0;
    
    //Check for dungeon boundaries
    try
    {
        if (characterRow < 0 || characterRow > (rows - 1) || characterCol < 0 || characterCol > (cols - 1))
        {
            throw AdventureErrors::BoundaryError("That's outside the dungeon's boundaries.");
        }
    }
    catch (const AdventureErrors::BoundaryError& e)
    {
        cout << e.what() << endl;
    }
    
    cout << "\n\n\n" << endl;
    cout << right << setw(102) << "               ~~***   4 ADJACENT ROOMS   ***~~               \n" << endl;
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
        cout << "\n";
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
        else if (toupper(roomContents[i] == 'K'))
        {
            cout << right << setw(55) << " " << left << "K - Kill Scroll" << endl;
        }
    }
    cout << endl;
    cout << setw(96) << right << "              ~~***   ***   ***~~               \n" << endl;
    cout << "\n\n\n" << endl;
    
}

/********************************************************************************************
 printMap
 Prints the layout of the dungeon with character's current position marked with a star "*".
 A different version of the map is displayed given the enum value passed to it.
 version = BASIC displays essentials only (treasure, gems & kill scroll)
 version = MONSTER displays monsters only
 version = ROOMOBJECT displays room objects only
 version = ITEM displays items only
 version = ALL displays all objects located in the dungeon
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
 _printAllMap
 Prints a map with all room objects, items and monsters in the dungeon.
 *******************************************************************************************/
void Dungeon::_printAllMap(int characterRow, int characterCol) const
{
    cout << "\n\n\n" << endl;
    cout << right << setw(100) << "               ~~***   GENERAL MAP   ***~~               \n" << endl;
    cout << setw(86) << " 0  1  2  3  4  5  6  7  8  9  " << endl;
    
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
            //Print all room object locations
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
            //Print all monsters locations
            else if (dungeonPtr[r][c].getMonsterPtr())
            {
                cout << " M ";
            }
            //Print all items locations
            else if (!dungeonPtr[r][c].getItems().empty())
            {
                //Gems
                if (dungeonPtr[r][c].contains("ruby") || dungeonPtr[r][c].contains("sapphire") || dungeonPtr[r][c].contains("emerald"))
                {
                    cout << " G ";
                }
                //Kill scroll
                else if (dungeonPtr[r][c].contains("kill scroll"))
                {
                    cout << " K ";
                }
                //Equipment & Potions
                else
                {
                    Equipment* ePtr = dynamic_cast<Equipment*>(*dungeonPtr[r][c].getItems().cbegin());
                    Potion* pPtr = dynamic_cast<Potion*>(*dungeonPtr[r][c].getItems().cbegin());
                    
                    if (ePtr)
                    {
                        cout << " E ";
                    }
                    else if (pPtr)
                    {
                        cout << " P ";
                    }
                    else
                    {
                        cout << "   ";
                    }
                }
            }
            else
            {
                cout << "   ";
            }
        }
        cout << left << r;
        cout << "\n";
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
 _printBasicMap
 Prints a map with locations of essentials necessary to win the game (treasure, gems & kill scroll).
 *******************************************************************************************/
void Dungeon::_printBasicMap(int characterRow, int characterCol) const
{
    cout << "\n\n\n" << endl;
    cout << right << setw(98) << "               ~~***   BASIC MAP   ***~~               \n" << endl;
    cout << setw(86) << " 0  1  2  3  4  5  6  7  8  9  " << endl;
    
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
                if (dungeonPtr[r][c].contains("ruby") || dungeonPtr[r][c].contains("sapphire") || dungeonPtr[r][c].contains("emerald"))
                {
                    cout << " G ";
                }
                else if (dungeonPtr[r][c].contains("kill scroll"))
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
        cout << "\n";
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
 _printItemsMap
 Prints a map with items only.
 *******************************************************************************************/
void Dungeon::_printItemsMap(int characterRow, int characterCol) const
{
    cout << "\n\n\n" << endl;
    cout << right << setw(98) << "               ~~***   ITEMS MAP   ***~~               \n" << endl;
    cout << setw(86) << " 0  1  2  3  4  5  6  7  8  9  " << endl;
    
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
            //Print all items location
            else if (!dungeonPtr[r][c].getItems().empty())
            {
                //Gem
                if (dungeonPtr[r][c].contains("ruby") || dungeonPtr[r][c].contains("sapphire") || dungeonPtr[r][c].contains("emerald"))
                {
                    cout << " G ";
                }
                //Kill scroll
                else if (dungeonPtr[r][c].contains("kill scroll"))
                {
                    cout << " K ";
                }
                //Equipment & Potion
                else
                {
                    Equipment* ePtr = dynamic_cast<Equipment*>(*dungeonPtr[r][c].getItems().cbegin());
                    Potion* pPtr = dynamic_cast<Potion*>(*dungeonPtr[r][c].getItems().cbegin());
                    if (ePtr)
                    {
                        cout << " E ";
                    }
                    else if (pPtr)
                    {
                        cout << " P ";
                    }
                    else
                    {
                        cout << "   ";
                    }
                }
            }
            else
            {
                cout << "   ";
            }
        }
        cout << left << r;
        cout << "\n";
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
    cout << right << setw(55) << " " << left << "P - Potion " << endl;
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
    cout << right << setw(100) << "               ~~***   MONSTER MAP   ***~~               \n" << endl;
    cout << setw(86) << " 0  1  2  3  4  5  6  7  8  9  " << endl;
    
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
            //Print monster's location
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
        cout << "\n";
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
    cout << right << setw(102) << "               ~~***   ROOM OBJECT MAP   ***~~               \n" << endl;
    cout << setw(86) << " 0  1  2  3  4  5  6  7  8  9  " << endl;
    
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
            //Print room object's location
            else if (dungeonPtr[r][c].getRoomObjectPtr())
            {
                RoomObject* temp = dungeonPtr[r][c].getRoomObjectPtr();
                Book* bPtr = dynamic_cast<Book*>(temp);
                Flare* fPtr = dynamic_cast<Flare*>(temp);
                Map* mPtr = dynamic_cast<Map*>(temp);
                Fountain* ftPtr = dynamic_cast<Fountain*>(temp);
                Treasure* tPtr = dynamic_cast<Treasure*>(temp);
                
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
                //Treasure
                else if (tPtr)
                {
                    cout << " T ";
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
        cout << "\n";
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
    cout << right << setw(55) << " " << left << "M - Map " << endl;
    cout << right << setw(55) << " " << left << "R - Fountain " << endl;
    cout << setw(96) << right << "              ~~***   ***   ***~~               \n" << endl;
    
    cout << "\n\n\n" << endl;
    
}

/********************************************************************************************
 _printContents
 Prints room contents of a room at row & col.
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
        
        //Treasure
        if (tPtr)
        {
            cout << " T ";
            return 'T';
        }
        //Book
        else if (bPtr)
        {
            cout << " B ";
            return 'B';
        }
        //Flare
        else if (fPtr)
        {
            cout << " F ";
            return 'F';
        }
        //Fountain
        else if (ftPtr)
        {
            cout << " R ";
            return 'R';
        }
        //Map
        else if (mPtr)
        {
            cout << " D ";
            return 'D';
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
        //Gems
        if (dungeonPtr[r][c].contains("ruby") || dungeonPtr[r][c].contains("sapphire") || dungeonPtr[r][c].contains("emerald"))
        {
            cout << " G ";
            return 'G';
        }
        //Kill scroll
        else if (dungeonPtr[r][c].contains("kill scroll"))
        {
            cout << " K ";
            return 'K';
        }
        //Equipment & Potions
        else
        {
            Equipment* ePtr = dynamic_cast<Equipment*>(*dungeonPtr[r][c].getItems().cbegin());
            Potion* pPtr = dynamic_cast<Potion*>(*dungeonPtr[r][c].getItems().cbegin());
            if (ePtr)
            {
                cout << " Q ";
                return 'Q';
            }
            else if (pPtr)
            {
                cout << " P ";
                return 'P';
            }
            else
            {
                cout << "   ";
            }
        }
    }
    else
    {
        cout << "   ";
    }
    
    return '1';
}

/********************************************************************************************
 putThingsIntoDungeon
 Sets monster, room object and item data for each room.
 *******************************************************************************************/
void Dungeon::putThingsIntoDungeon(const int &numMonsters, const int &numPots, const int &numEquipment, const int &numRoomObjs)
{
    //2D array of bools used to indicate whether a room was initialized or not
    bool roomData[10][10] = {false};
    Generation spawner;
    
    //Put monster and treasure in room 0, 4
    roomData[0][4] = true;
    dungeonPtr[0][4].setMonsterPtr(spawner.generateMonster(spawner.DRAGONBOSS)); // generates dragonboss at 0,4
    dungeonPtr[0][4].setRoomObjectPtr(spawner.generateRoomObj(spawner.TREASURE)); // generates treasure at 0,4
    
    //Put kill scroll in room 2, 6
    roomData[2][6] = true;
    dungeonPtr[2][6].setItem(spawner.generateItem(spawner.KILLSCROLL)); // generates KillScroll at 2, 6
    
    //Put ruby in room 3, 1
    roomData[3][1] = true;
    dungeonPtr[3][1].setItem(spawner.generateItem(spawner.RUBY)); // generates Ruby at 3,1
    
    //Put sapphire in room 4, 7
    roomData[4][7] = true;
    dungeonPtr[4][7].setItem(spawner.generateItem(spawner.SAPPHIRE)); // generates Sapphire at 4,7
    
    //Put emerald in room 8, 1
    roomData[8][1] = true;
    dungeonPtr[8][1].setItem(spawner.generateItem(spawner.EMERALD)); // generates Emerald at 8,1
    
    //Initialize monster, potion, equipment and room object counts
    int monsterCount = 0;
    int potCount = 0;
    int equipmentCount = 0;
    int roomObjCount = 0;
    int rowNum, colNum;
    do
    {
        //Generate room coordinates
        rowNum = rand() % rows;
        colNum = rand() % cols;
        
        //If the room is empty
        if(!roomData[rowNum][colNum])
        {
            //Keep allocating monsters until you hit target number of monsters
            if(monsterCount != numMonsters)
            {
                dungeonPtr[rowNum][colNum].setMonsterPtr(spawner.generateMonster((Generation::MONSTERS)(rand() % (spawner.monsterContainer.size() - 1))));
                
                //Allocate an item to each room with a monster (monster guards the item)
                dungeonPtr[rowNum][colNum].setItem(spawner.generateItem((Generation::ITEMS)(rand() % 5)));
                monsterCount++;
            }
            
            //Keep allocating potions until you hit target number of potions
            else if(potCount != numPots)
            {
                dungeonPtr[rowNum][colNum].setItem(spawner.generateItem((Generation::ITEMS)(rand() % 5))); // put this into the room
                potCount++;
            }
            
            //Keep allocating equipment until you hit the target equipment count
            else if(equipmentCount != numEquipment)
            {
                //rand() % ((spawner.itemContainer.size() - (11 + 3)) + 11) generates a random number between 11 and 25 (which is the first of equipment and last of equipment, except iron)
                dungeonPtr[rowNum][colNum].setItem(spawner.generateItem((Generation::ITEMS)(rand() % (spawner.itemContainer.size() - (11 + 3)) + 11)));
                equipmentCount++;
            }
            
            //Keep allocating room objects until you hit the target number of room objects
            else if(roomObjCount != numRoomObjs)
            {
                dungeonPtr[rowNum][colNum].setRoomObjectPtr(spawner.generateRoomObj((Generation::ROOMOBJ)(rand() % (spawner.roomObjContainer.size() - 1))));
                roomObjCount++;
            }
            
            //Set room status to initialized
            roomData[rowNum][colNum] = true;
        }
    } while(monsterCount != numMonsters || potCount != numPots || equipmentCount != numEquipment || roomObjCount != numRoomObjs);
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

