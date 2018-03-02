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
Dungeon::Dungeon(int r, int c) throw(FileOpenError) : rows(r), cols(c), numPopulatedRooms(0)
{
    //Allocate memory for the dungeon
    alloc();
    
    //Initialize vectors with all room contents (monsters, items, room objects)
    addRoomContents();
    
    //Set room coordinates and wall data
    const char fileName[] = "/Users/Agnieszka Rynkiewicz/Desktop/Computer Science/1.7 C++/1.1 C++ Courses/1.3 Advanced C++/1.0 Group Project/3.0 Code/walls.bin";
    
    //Open file with room data
    fstream file;
    try
    {
        file.open(fileName, ios::in | ios::binary);
        if (!file)
        {
            throw FileOpenError(fileName);
        }
    }
    catch (const FileOpenError& e)
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
    
    //Close file
    file.close();
}

/********************************************************************************************
 addRoomContents
 Initializes vectors with all monsters, items and room objects with data.
 Returns true if all vectors were populated successfully.
 *******************************************************************************************/
bool Dungeon::addRoomContents() throw(bad_alloc)
{
    try
    {
        //Initialize vector with all monsters in the dungeon
        for (int i = 0; i < 25; i++)
        {
            switch (i % 2)
            {
                //Allocate a dragon
                case 0:
                {
                    monsters.push_back(new Dragon("Dragon", "This giant fire-spewing three-headed winged monster looks strong and intimidating. If he's really angry, he'll throw fireballs at you! Watch out!"));
                    //cout << "NO: " << i << endl;
                    //Monster* ptr = monsters[monsters.size() - 1];
                    //cout << "MONSTER NAME: " << ptr->getName() << endl;
                    //cout << "MONSTER DESC: " << ptr->getDescription() << endl;
                    break;
                }
                //Allocate a titan
                case 1:
                {
                    monsters.push_back(new Titan("Titan", "This gigantic humanlike creature can crush you in no time. If you're not careful, he can knock down your equipment."));
                    //cout << "NO: " << i << endl;
                    //Monster* ptr = monsters[monsters.size() - 1];
                    //cout << "MONSTER NAME: " << ptr->getName() << endl;
                    //cout << "MONSTER DESC: " << ptr->getDescription() << endl;
                    break;
                }
                default:
                {
                    //To account for the first loop iteration resulting in 0 % 2 = 2
                    monsters.push_back(new Dragon("Dragon", "This giant fire-spewing three-headed winged monster looks strong and intimidating. If he's really angry, he'll throw fireballs at you! Watch out!"));
                    //cout << "NO: " << i << endl;
                    //Monster* ptr = monsters[monsters.size() - 1];
                    //cout << "MONSTER NAME: " << ptr->getName() << endl;
                    //cout << "MONSTER DESC: " << ptr->getDescription() << endl;
                    break;
                }
            }
        }
        
        //Initialize dragonboss pointer
        dragonBoss = new DragonBoss("DragonBoss", "So you have found the biggest and scariest dragon in this dungeon that guards this place's treasures. Only a few moments separate you from becoming rich and winning the fame and glory of a great warrior you came here for. The only thing you have to do is face this bad-tempered oversized colossus. Remember he can hurl fireballs your way and knock down any of your equipment. Good luck! Become a legend or become dinner!");
        //cout << "MONSTER NAME: " << dragonBoss->getName() << endl;
        //cout << "MONSTER DESC: " << dragonBoss->getDescription() << endl;
        
        //Initialize items vector
        for (int i = 0; i < 25; i++)
        {
            switch(i % 26)
            {
                case 0:
                {
                    items.push_back(new HealthPotion());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 1:
                {
                    items.push_back(new MaxHealthPotion());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 2:
                {
                    items.push_back(new StrengthPotion());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 3:
                {
                    items.push_back(new IntPotion());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 4:
                {
                    items.push_back(new LuckPotion());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 5:
                {
                    items.push_back(new KillScroll());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 6:
                {
                    items.push_back(new IronHelmet());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 7:
                {
                    items.push_back(new SteelHelmet());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 8:
                {
                    items.push_back(new MithrilHelmet());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 9:
                {
                    items.push_back(new AdamantineHelmet());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 10:
                {
                    items.push_back(new IronArmor());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 11:
                {
                    items.push_back(new SteelArmor());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 12:
                {
                    items.push_back(new MithrilArmor());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 13:
                {
                    items.push_back(new AdamantineHelmet());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 14:
                {
                    items.push_back(new IronGreaves());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 15:
                {
                    items.push_back(new SteelGreaves());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 16:
                {
                    items.push_back(new MithrilGreaves());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 17:
                {
                    items.push_back(new AdamantineGreaves());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 18:
                {
                    items.push_back(new IronSword());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 19:
                {
                    items.push_back(new SteelSword());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 20:
                {
                    items.push_back(new MithrilSword());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 21:
                {
                    items.push_back(new AdamantineSword());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 22:
                {
                    items.push_back(new IronDagger());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 23:
                {
                    items.push_back(new SteelDagger());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 24:
                {
                    items.push_back(new MithrilDagger());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                case 25:
                {
                    items.push_back(new AdamantineDagger());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
                default:
                {
                    //To account for first loop iteration resulting in 0 % 26 = 26
                    items.push_back(new HealthPotion());
                    //cout << "NO: " << i << endl;
                    //Item* ptr = items[items.size() - 1];
                    //cout << "ITEM NAME: " << ptr->name() << endl;
                    //cout << "ITEM DESC: " << ptr->description() << endl;
                    break;
                }
            }
        }
        
        //Initialize gem pointers
        ruby = new Ruby;
        sapphire = new Sapphire;
        emerald = new Emerald;
        
        //cout << "ITEM NAME: " << ruby->name() << endl;
        //cout << "ITEM DESC: " << ruby->description() << endl;
        //cout << "ITEM NAME: " << sapphire->name() << endl;
        //cout << "ITEM DESC: " << sapphire->description() << endl;
        //cout << "ITEM NAME: " << emerald->name() << endl;
        //cout << "ITEM DESC: " << emerald->description() << endl;
        
        
        //Initialize room objects vector
        for (int i = 0; i < 25; i++)
        {
            switch (i % 4)
            {
                case 0:
                {
                    roomObjects.push_back(new Book("book", "This black leather book contains hints about how to win the game"));
                    //cout << "NO: " << i << endl;
                    //RoomObject* ptr = roomObjects[roomObjects.size() - 1];
                    //cout << "ROOM OBJECT NAME: " << ptr->getName() << endl;
                    //cout << "ROOM OBJECT DESC: " << ptr->getDescription() << endl;
                    break;
                }
                case 1:
                {
                    roomObjects.push_back(new Flare("flare", "You can use this flare to check what's inside four adjacent rooms!!!"));
                    //cout << "NO: " << i << endl;
                    //RoomObject* ptr = roomObjects[roomObjects.size() - 1];
                    //cout << "ROOM OBJECT NAME: " << ptr->getName() << endl;
                    //cout << "ROOM OBJECT DESC: " << ptr->getDescription() << endl;
                    break;
                }
                case 2:
                {
                    roomObjects.push_back(new Fountain("fountain", "This fountain may help you recover or make you ill. Do you want to take the risk?"));
                    //cout << "NO: " << i << endl;
                    //RoomObject* ptr = roomObjects[roomObjects.size() - 1];
                    //cout << "ROOM OBJECT NAME: " << ptr->getName() << endl;
                    //cout << "ROOM OBJECT DESC: " << ptr->getDescription() << endl;
                    break;
                }
                case 3:
                {
                    roomObjects.push_back(new Map("map", "You find this large map hanging on the wall. You can use it to check where the gems, monsters, and treaseure are."));
                    //cout << "NO: " << i << endl;
                    //RoomObject* ptr = roomObjects[roomObjects.size() - 1];
                    //cout << "ROOM OBJECT NAME: " << ptr->getName() << endl;
                    //cout << "ROOM OBJECT DESC: " << ptr->getDescription() << endl;
                    break;
                }
                default:
                {
                    //To account for first loop iteration resulting in 0 % 4 = 4
                    roomObjects.push_back(new Book("book", "This black leader book contains hints about how to win the game"));
                    //cout << "NO: " << i << endl;
                    //RoomObject* ptr = roomObjects[roomObjects.size() - 1];
                    //cout << "ROOM OBJECT NAME: " << ptr->getName() << endl;
                    //cout << "ROOM OBJECT DESC: " << ptr->getDescription() << endl;
                    break;
                    
                }
            }
        }
        
        //Initialize treasure pointer
        treasure = new Treasure("treasure", "You have found your riches! In front of you is a chest full of gold coins, gemstones and other valuables! You have successfully accomplished your mission. Congratulations!");
        //cout << "ROOM OBJECT NAME: " << treasure->getName() << endl;
        //cout << "ROOM OBJECT DESC: " << treasure->getDescription() << endl;
    }
    catch (bad_alloc)
    {
        cout << "Insufficient memory." << endl;
    }
    return true;
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
    
    cout << "ROW OF THIS ROOM: " << dungeonPtr[r][c].getRow() << endl;
    cout << "COL OF THIS ROOM: " << dungeonPtr[r][c].getCol() << endl;
    
    //Set treasure
    if (r == 0 && c == 4)
    {
        dungeonPtr[r][c].setRoomObjectPtr(treasure);
        dungeonPtr[r][c].setMonsterPtr(dragonBoss);
        
        if (dungeonPtr[r][c].getMonsterPtr())
        {
            cout << "r: " << r << "c" << c << " " << dungeonPtr[r][c].getMonsterPtr()->getName() << endl;
        }
        if (dungeonPtr[r][c].getRoomObjectPtr())
        {
            cout << "r: " << r << "c" << c << " " << dungeonPtr[r][c].getRoomObjectPtr()->getName() << endl;
        }
        
    }
    //Set ruby, sapphire and emerald
    else if (r == 3 && c == 1)
    {
        dungeonPtr[r][c].setItem(ruby);
        vector<Item*> newItemVect = dungeonPtr[r][c].getItems();
        cout << "r: " << r << "c" << c << " " << newItemVect[0]->name() << endl;
        cout << "r: " << r << "c" << c << " " << newItemVect[0]->description() << endl;
    }
    else if (r == 4 && c == 7)
    {
        dungeonPtr[r][c].setItem(sapphire);
        vector<Item*> newItemVect = dungeonPtr[r][c].getItems();
        cout << "r: " << r << "c" << c << " " << newItemVect[0]->name() << endl;
        cout << "r: " << r << "c" << c << " " << newItemVect[0]->description() << endl;
    }
    else if (r == 8 && c == 1)
    {
        dungeonPtr[r][c].setItem(emerald);
        vector<Item*> newItemVect = dungeonPtr[r][c].getItems();
        cout << "r: " << r << "c" << c << " " << newItemVect[0]->name() << endl;
        cout << "r: " << r << "c" << c << " " << newItemVect[0]->description() << endl;
    }
    //Set monster, room object, and item data
    else
    {
        bool ptrWasSet = false;
        while (!ptrWasSet)
        {
            //Generate a random number
            int i = rand()% 4 + 1;
            //cout << "i: " << i << endl;
            switch(i)
            {
                //Set monster data
                case 1:
                {
                    if ((!monsters.empty()))
                    {
                        //Set monster Ptr in the room to monster Ptr stored as last element in monster vector
                        dungeonPtr[r][c].setMonsterPtr(monsters[monsters.size() - 1]);
                        monsters.pop_back();
                        cout << "r: " << r << "c" << c << " " << dungeonPtr[r][c].getMonsterPtr()->getName() << endl;
                        ptrWasSet = true;
                    }
                    break;
                }
                //Set room object data
                case 2:
                {
                    if (!roomObjects.empty())
                    {
                        //Set room object Ptr in the room to room object Ptr stored as last element in room object vector
                        dungeonPtr[r][c].setRoomObjectPtr(roomObjects[roomObjects.size() - 1]);
                        roomObjects.pop_back();
                        cout << "r: " << r << "c" << c << " " << dungeonPtr[r][c].getRoomObjectPtr()->getName() << endl;
                        ptrWasSet = true;
                    }
                    break;
                }
                //Set item data
                case 3:
                {
                    if (!items.empty())
                    {
                        //Set item Ptr in the room to item Ptr stored as last element in items vector
                        dungeonPtr[r][c].setItem(items[items.size() - 1]);
                        items.pop_back();
                        
                        vector<Item*> newItemVect = dungeonPtr[r][c].getItems();
                        for (int i = 0; i < newItemVect.size(); i++)
                        {
                            //cout << "i: " << i << endl;
                            cout << "r: " << r << "c" << c << " " << newItemVect[i]->name() << endl;
                        }
                        
                        ptrWasSet = true;
                    }
                    break;
                }
                //Set an empty room
                case 4:
                {
                    cout << "Empty" << endl;
                    ptrWasSet = true;
                    break;
                }
            }
        }
    }
    
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
 Prints the layout of the dungeon with character's current position marked with an x.
 *******************************************************************************************/
void Dungeon::printMap(int characterX, int characterY) const
{
    bool eastSet;
    cout << " _ _ _ " << endl;
    cout << "You are at " << characterX << " " << characterY << endl; //ADDED
    for (auto i = 0; i < rows; i++)
    {
        for (auto j = 0; j < cols; j++)
        {
            eastSet = false;
            //Check if eastern wall was set for the previous room
            if (j > 0)
            {
                eastSet = !dungeonPtr[i][j - 1].checkEast();
            }
            dungeonPtr[i][j].print(eastSet);
        }
        cout << endl;
    }
}

/********************************************************************************************
 printMap
 Takes room coordinates as arguments and prints room contents of 4 adjacent rooms.
 *******************************************************************************************/
void Dungeon::printAdjacentRooms(int r, int c) const throw (BoundaryError)
{
    //Check for dungeon boundaries
    try
    {
        if (r < 0 || r > (rows - 1) || c < 0 || c > (cols - 1))
        {
            throw BoundaryError("Error: These coordinates are outsie the dungeon's boundaries");
        }
    }
    catch (const BoundaryError& e)
    {
        cout << e.what() << endl;
    }
    
    //Print Room contents for the room NORTH
    if (r == 0)
    {
        cout << "There is no room NORTH of you.\n" << endl;
    }
    else
    {
        cout << "In the room NORTH of you there is a(n): ";
        if (dungeonPtr[r - 1][c].getMonsterPtr())
        {
            cout << dungeonPtr[r - 1][c].getMonsterPtr()->getName() << endl;
        }
        else if (dungeonPtr[r - 1][c].getRoomObjectPtr())
        {
            cout << dungeonPtr[r - 1][c].getRoomObjectPtr()->getName() << endl;
        }
        else if (!dungeonPtr[r - 1][c].getItems().empty())
        {
            for (int i = 0; i < items.size(); i++)
            {
                Item* temp = items[i];
                if (temp != nullptr)
                {
                    cout << temp->name() << " ";
                }
            }
            cout << endl;
        }
        else
        {
            cout << "The room NORTH of you is empty.\n" << endl;
        }
        cout << endl;
    }
    
    
    //Print Room contents for the room SOUTH
    if (r == (rows - 1))
    {
        cout << "There is no room SOUTH of you.\n" << endl;
    }
    else
    {
        cout << "In the room SOUTH of you there is a(n): ";
        if (dungeonPtr[r + 1][c].getMonsterPtr())
        {
            cout << dungeonPtr[r + 1][c].getMonsterPtr()->getName() << endl;
        }
        else if (dungeonPtr[r + 1][c].getRoomObjectPtr())
        {
            cout << dungeonPtr[r + 1][c].getRoomObjectPtr()->getName() << endl;
        }
        else if (!dungeonPtr[r + 1][c].getItems().empty())
        {
            for (int i = 0; i < items.size(); i++)
            {
                Item* temp = items[i];
                if (temp != nullptr)
                {
                    cout << temp->name() << " ";
                }
            }
        }
        else
        {
            cout << "The room SOUTH of you is empty.\n" << endl;
        }
        cout << endl;
    }
    
    //Print Room contents for the room EAST
    if (c == (cols - 1))
    {
        cout << "There is no room EAST of you.\n" << endl;
    }
    else
    {
        cout << "In the room EAST of you there is a(n): ";
        if (dungeonPtr[r][c + 1].getMonsterPtr())
        {
            cout << dungeonPtr[r][c + 1].getMonsterPtr()->getName() << endl;
        }
        else if (dungeonPtr[r][c + 1].getRoomObjectPtr())
        {
            cout << dungeonPtr[r][c + 1].getRoomObjectPtr()->getName() << endl;
        }
        else if (!dungeonPtr[r][c + 1].getItems().empty())
        {
            for (int i = 0; i < items.size(); i++)
            {
                Item* temp = items[i];
                if (temp != nullptr)
                {
                    cout << temp->name() << " ";
                }
            }
        }
        else
        {
            cout << "The room EAST of you is empty.\n" << endl;
        }
        cout << endl;
    }
    
    //Print Room contents for the room WEST
    if (c == 0)
    {
        cout << "There is no room WEST of you.\n" << endl;
    }
    else
    {
        cout << "In the room WEST of you there is a(n): " << " ";
        if (dungeonPtr[r][c - 1].getMonsterPtr())
        {
            cout << dungeonPtr[r][c - 1].getMonsterPtr()->getName() << endl;
        }
        else if (dungeonPtr[r][c - 1].getRoomObjectPtr())
        {
            cout << dungeonPtr[r][c - 1].getRoomObjectPtr()->getName() << endl;
        }
        else if (!dungeonPtr[r][c - 1].getItems().empty())
        {
            for (int i = 0; i < items.size(); i++)
            {
                Item* temp = items[i];
                if (temp != nullptr)
                {
                    cout << temp->name() << " ";
                }
            }
        }
        else
        {
            cout << "The room WEST of you is empty.\n" << endl;
        }
        cout << endl;
    }
    cout << endl;
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

