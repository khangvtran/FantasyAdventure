//
//  Generation.h
//  Character

//  The way you use this class is to initialize a local instance of this class with its default constructor.
//  Then based on your required generation, you will call the generate functions as shown below. The generate functions will return an object of the type passed to it as a string.
// WARNINGS: You are to call the spawner.<somecontainer>.at("<yourstring>") function and it will throw out_of_range error
//           THE GENERATE FUNCTIONS SHOULD NEVER RETURN A nullptr SO IF IT DOES PLEASE LET ME KNOW.


/* SAMPLE CODE
 Generation spawner;
 try {
    Item* thing = spawner.generateItem(spawner.itemContainer.at("some item string"));
    if(thing != nullptr) // this shouldn't ever be nullptr
    {
        // do code with thing.
    }
 
    RoomObject* ro = spawner.generateRoomObj(spawner.roomObjectContainer.at("Book"), "<bookname>", "<bookdescription>"); // returns a book object
    if(ro != nullptr)
    {
        // do code with ro
    }
 
    Monster* monster = spawner.generateMonster(spawner.monsterContainer.at("Dragon"), "<monstername>", "<monsterdescription>"); // returns a Dragon object
    if(monster != nullptr)
    {
        // do code with monster
    }
 
 } catch (out_of_range &err) {
    cerr << "Invalid type " << endl << endl;
 }
 END CODE SAMPLE */

//  Created by Joshua Kuan on 02/03/2018.
//  Copyright © 2018 Joshua Kuan. All rights reserved.
//

#ifndef Generation_h
#define Generation_h
#include "Monster.h"
#include "Item.h"
#include "RoomObject.h"

#include <unordered_map>
#include <string>

class Generation
{
public:
    enum ITEMS {
        HEALTHPOTION, MAXHEALTHPOTION, STRENGTHPOTION, INTPOTION, LUCKPOTION, KILLSCROLL,
        IRONHELMET, STEELHELMET, MITHRILHELMET, ADAMANTINEHELMET,
        IRONARMOR, STEELARMOR, MITHRILARMOR, ADAMANTINEARMOR,
        IRONGREAVES, STEELGREAVES, MITHRILGREAVES, ADAMANTINEGREAVES,
        IRONSWORD, STEELSWORD, MITHRILSWORD, ADAMANTINESWORD,
        IRONDAGGER, STEELDAGGER, MITHRILDAGGER, ADAMANTINEDAGGER,
        RUBY, EMERALD, SAPPHIRE};
    
    std::unordered_map<string, ITEMS> itemContainer {
        {"Health Potion", HEALTHPOTION}, {"Max Health Potion", MAXHEALTHPOTION}, {"Strength Potion", STRENGTHPOTION}, {"Int Potion", INTPOTION},
        {"Luck Potion", LUCKPOTION}, {"Kill Scroll", KILLSCROLL},
        {"Iron Helmet", IRONHELMET}, {"Steel Helmet", STEELHELMET}, {"Mithril Helmet", MITHRILHELMET}, {"Adamantine Helmet", ADAMANTINEHELMET},
        {"Iron Greaves", IRONGREAVES}, {"Steel Greaves", STEELGREAVES}, {"Mithril Greaves", MITHRILGREAVES}, {"Adamantine Greaves", ADAMANTINEGREAVES},
        {"Iron Sword", IRONSWORD}, {"Steel Sword", STEELSWORD}, {"Mithril Sword", MITHRILSWORD}, {"Adamantine Sword", ADAMANTINESWORD},
        {"Iron Dagger", IRONDAGGER}, {"Steel Dagger", STEELDAGGER}, {"Mithril Dagger", MITHRILDAGGER}, {"Adamantine Dagger", ADAMANTINEDAGGER},
        {"Ruby", RUBY}, {"Emerald", EMERALD}, {"Sapphire", SAPPHIRE}
    };
    
    enum MONSTERS {DRAGON, TITAN, DRAGONBOSS};
    std::unordered_map<string, MONSTERS> monsterContainer {
        {"Dragon", DRAGON}, {"Titan", TITAN}, {"DragonBoss", DRAGONBOSS}
    };
    
    enum ROOMOBJ {BOOK, FLARE, FOUNTAIN, MAP, TREASURE};
    std::unordered_map<string, ROOMOBJ> roomObjContainer {
        {"Book", BOOK}, {"Flare", FLARE}, {"Fountain", FOUNTAIN}, {"Map", MAP}, {"Treasure", TREASURE}
    };
    
    Monster* generateMonster(MONSTERS type, const string& = "", const string& = "");
    Item* generateItem(ITEMS type);
    RoomObject* generateRoomObj(ROOMOBJ type, const string& = "", const string& = "");
    
};

#endif /* Generation_h */
