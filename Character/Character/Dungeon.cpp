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
    
    //Close file
    file.close();
}
/*
bool Dungeon::putthingsintodungeon()
{
    bool roomData[10][10] = {false};
    Generation spawner;
    
    do
    {
        int rowNum = rand() % 10;
        int colNum = rand() % 10;
        
        bool set = false;
        while(!roomData[rowNum][colNum] && !set) // if room is empty and no monster
        {
            if(!roomData[rowNum][colNum])
                dungeonPtr[rowNum][colNum].setMonsterPtr(spawner.generateMonster(spawner.monsterContainer[0])); // generates dragon
            set = true;
        }
        if(!roomData[rowNum][colNum]) // if room is empty
        {
            
        }
    }
    
    
    
    
    
    const int numMonsters = 18;
    const int pots = 15;
    const int equipment = 20;
    const int roomobjs = 20;
    int monsterCount, potCount, equipmentCount, roomobjCount = 0;
    
    
    while(monsterCount != numMonsters && potCount != pots && equipmentCount != equipment && roomobjCount != roomobjs)
    {
        
        int rowNum = rand() % 10;
        int colNum = rand() % 10;
        
        if(!roomData[rowNum][colNum]) // if room is empty
        {
            if(monsterCount != numMonsters)
            {
                spawner.generateMonster(<#Generation::MONSTERS type#>)
            }
        }
        
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                if(! roomData[i][j]) // if room is empty
                {
                    
                }
            }
        }
    }
    
}*/
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
                    roomObjects.push_back(new Book("book", "This black leather book contains hints about how to win the game."));
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
                    roomObjects.push_back(new Book("book", "This black leader book contains hints about how to win the game."));
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
    
    //cout << "ROW OF THIS ROOM: " << dungeonPtr[r][c].getRow() << endl;
    //cout << "COL OF THIS ROOM: " << dungeonPtr[r][c].getCol() << endl;
    
    //Set treasure
    if (r == 0 && c == 4)
    {
        dungeonPtr[r][c].setRoomObjectPtr(treasure);
        dungeonPtr[r][c].setMonsterPtr(dragonBoss);
        
        if (dungeonPtr[r][c].getMonsterPtr())
        {
            //cout << "r: " << r << "c" << c << " " << dungeonPtr[r][c].getMonsterPtr()->getName() << endl;
        }
        if (dungeonPtr[r][c].getRoomObjectPtr())
        {
            //cout << "r: " << r << "c" << c << " " << dungeonPtr[r][c].getRoomObjectPtr()->getName() << endl;
        }
        
    }
    //Set ruby, sapphire and emerald
    else if (r == 3 && c == 1)
    {
        dungeonPtr[r][c].setItem(ruby);
        //vector<Item*> newItemVect = dungeonPtr[r][c].getItems();
        //cout << "r: " << r << "c" << c << " " << newItemVect[0]->name() << endl;
        //cout << "r: " << r << "c" << c << " " << newItemVect[0]->description() << endl;
    }
    else if (r == 4 && c == 7)
    {
        dungeonPtr[r][c].setItem(sapphire);
        //vector<Item*> newItemVect = dungeonPtr[r][c].getItems();
        //cout << "r: " << r << "c" << c << " " << newItemVect[0]->name() << endl;
        //cout << "r: " << r << "c" << c << " " << newItemVect[0]->description() << endl;
    }
    else if (r == 8 && c == 1)
    {
        dungeonPtr[r][c].setItem(emerald);
        //vector<Item*> newItemVect = dungeonPtr[r][c].getItems();
        //cout << "r: " << r << "c" << c << " " << newItemVect[0]->name() << endl;
        //cout << "r: " << r << "c" << c << " " << newItemVect[0]->description() << endl;
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
                        //cout << "r: " << r << "c" << c << " " << dungeonPtr[r][c].getMonsterPtr()->getName() << endl;
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
                        //cout << "r: " << r << "c" << c << " " << dungeonPtr[r][c].getRoomObjectPtr()->getName() << endl;
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
                        
                        /*
                        vector<Item*> newItemVect = dungeonPtr[r][c].getItems();
                        for (int i = 0; i < newItemVect.size(); i++)
                        {
                            //cout << "i: " << i << endl;
                            cout << "r: " << r << "c" << c << " " << newItemVect[i]->name() << endl;
                        }
                         */
                        
                        ptrWasSet = true;
                    }
                    break;
                }
                //Set an empty room
                case 4:
                {
                    //cout << "Empty" << endl;
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
 Prints the layout of the dungeon with character's current position marked with a star "*".
 Prints the location of treasure, the three gems (ruby, sapphire, emerald) and all
 monsters in the dungeon.
 *******************************************************************************************/
void Dungeon::printMap(int characterRow, int characterCol) const
{
    cout << "\n\n\n" << endl;
    cout << setw(96) << "               ~~***   MAP   ***~~               \n" << endl;
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
           
            //Print monster's location
            else if (dungeonPtr[r][c].getMonsterPtr())
            {
                cout << " M ";
            }
            else if (!dungeonPtr[r][c].getItems().empty())
            {
                vector<Item*> temp = dungeonPtr[r][c].getItems();
                Ruby* rPtr =  dynamic_cast<Ruby*>(temp[0]);
                Sapphire* sPtr =  dynamic_cast<Sapphire*>(temp[0]);
                Emerald* ePtr = dynamic_cast<Emerald*>(temp[0]);
                
                if (rPtr || sPtr || ePtr)
                {
                    cout << " G ";
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
    cout << right << setw(55) << " " << left << "M - Monster " << endl;
    cout << right << setw(55) << " " << left << "G - Gem (Ruby, Sapphire, Emerald)\n" << endl;
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
    cout << setw(96) << "               ~~***   ***   ***~~               \n" << endl;
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
    bool consUsed = false;
    
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
        else if (toupper(roomContents[i]) == 'P' && !mapUsed)
        {
            cout << right << setw(55) << " " << left << "P - Map " << endl;
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
        else if (toupper(roomContents[i]) == 'C' && !consUsed)
        {
            cout << right << setw(55) << " " << left << "C - Consummable\n" << endl;
            consUsed = true;
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
            cout << " P ";
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
        Ruby* rPtr =  dynamic_cast<Ruby*>(temp[0]);
        Sapphire* sPtr =  dynamic_cast<Sapphire*>(temp[0]);
        Emerald* ePtr = dynamic_cast<Emerald*>(temp[0]);
        Equipment* qPtr = dynamic_cast<Equipment*>(temp[0]);
        
        if (rPtr || sPtr || ePtr)
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
            cout << " C ";
            return 'C';
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
