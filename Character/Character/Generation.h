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
 
    RoomObject* ro = spawner.generateRoomObj(spawner.roomObjectContainer.at("Book")); // returns a book object
    if(ro != nullptr)
    {
        // do code with ro
    }
 
    Monster* monster = spawner.generateMonster(spawner.monsterContainer.at("Dragon")); // returns a Dragon object
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
        HEALTHPOTION, MAXHEALTHPOTION, STRENGTHPOTION, INTPOTION, LUCKPOTION, KILLSCROLL, // 0-4 potions, 5 kill scroll
        IRONHELMET, IRONARMOR, IRONGREAVES, IRONSWORD, IRONDAGGER, // 6-10 iron things
        STEELHELMET, STEELARMOR, STEELGREAVES, STEELSWORD, STEELDAGGER, // 11-15 steel things
        MITHRILHELMET, MITHRILARMOR, MITHRILGREAVES, MITHRILSWORD, MITHRILDAGGER, // 16-20 mithril things
        ADAMANTINEHELMET, ADAMANTINEARMOR, ADAMANTINEGREAVES, ADAMANTINESWORD, ADAMANTINEDAGGER, // 21-25 adamantine things
        RUBY, EMERALD, SAPPHIRE }; // 26-28 gems
    
    std::unordered_map<std::string, ITEMS> itemContainer {
        {"health potion", HEALTHPOTION}, {"max health potion", MAXHEALTHPOTION}, {"strength potion", STRENGTHPOTION}, {"intelligence potion", INTPOTION},
        {"luck potion", LUCKPOTION}, {"kill scroll", KILLSCROLL},
        {"iron helmet", IRONHELMET}, {"steel helmet", STEELHELMET}, {"mithril helmet", MITHRILHELMET}, {"adamantine helmet", ADAMANTINEHELMET},
        {"iron armor", IRONARMOR}, {"steel armor", STEELARMOR}, {"mithril armor", MITHRILARMOR}, {"adamantine armor", ADAMANTINEARMOR},
        {"iron greaves", IRONGREAVES}, {"steel greaves", STEELGREAVES}, {"mithril greaves", MITHRILGREAVES}, {"adamantine greaves", ADAMANTINEGREAVES},
        {"iron sword", IRONSWORD}, {"steel sword", STEELSWORD}, {"mithril sword", MITHRILSWORD}, {"adamantine sword", ADAMANTINESWORD},
        {"iron dagger", IRONDAGGER}, {"steel dagger", STEELDAGGER}, {"mithril dagger", MITHRILDAGGER}, {"adamantine dagger", ADAMANTINEDAGGER},
        {"ruby", RUBY}, {"emerald", EMERALD}, {"sapphire", SAPPHIRE}
    };
    
    enum MONSTERS {DRAGON, TITAN, DRAGONBOSS};
    std::unordered_map<std::string, MONSTERS> monsterContainer {
        {"Dragon", DRAGON}, {"Titan", TITAN}, {"DragonBoss", DRAGONBOSS}
    };
    
    enum ROOMOBJ {BOOK, FLARE, FOUNTAIN, MAP, TREASURE};
    std::unordered_map<std::string, ROOMOBJ> roomObjContainer {
        {"Book", BOOK}, {"Flare", FLARE}, {"Fountain", FOUNTAIN}, {"Map", MAP}, {"Treasure", TREASURE}
    };
    
    Monster* generateMonster(MONSTERS type);
    Item* generateItem(ITEMS type);
    RoomObject* generateRoomObj(ROOMOBJ type);
    
};

#endif /* Generation_h */
