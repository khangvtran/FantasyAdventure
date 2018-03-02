//
//  Generation.h
//  Character
//
//  Created by Joshua Kuan on 02/03/2018.
//  Copyright © 2018 Khang Tran. All rights reserved.
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
    enum ITEMS { HEALTHPOTION, MAXHEALTHPOTION, STRENGTHPOTION, INTPOTION, LUCKPOTION, KILLSCROLL, IRONHELMET, STEELHELMET, MITHRILHELMET, ADAMANTINEHELMET, IRONARMOR, STEELARMOR, MITHRILARMOR, ADAMANTINEARMOR, IRONGREAVES, STEELGREAVES, MITHRILGREAVES, ADAMANTINEGREAVES, IRONSWORD, STEELSWORD, MITHRILSWORD, ADAMANTINESWORD, IRONDAGGER, STEELDAGGER, MITHRILDAGGER, ADAMANTINEDAGGER };
    
    std::unordered_map<string, ITEMS> itemContainer {
        {"Health Potion", HEALTHPOTION}, {"Max Health Potion", MAXHEALTHPOTION}, {"Strength Potion", STRENGTHPOTION}, {"Int Potion", INTPOTION},
        {"Luck Potion", LUCKPOTION}, {"Kill Scroll", KILLSCROLL},  {"Iron Helmet", IRONHELMET}, {"Steel Helmet", STEELHELMET}, {"Mithril Helmet", MITHRILHELMET},
        {"Adamantine Helmet", ADAMANTINEHELMET}, {"Iron Greaves", IRONGREAVES}, {"Steel Greaves", STEELGREAVES}, {"Mithril Greaves", MITHRILGREAVES},
        {"Adamantine Greaves", ADAMANTINEGREAVES}, {"Iron Sword", IRONSWORD}, {"Steel Sword", STEELSWORD}, {"Mithril Sword", MITHRILSWORD},
        {"Iron Dagger", IRONDAGGER}, {"Steel Dagger", STEELDAGGER}, {"Mithril Dagger", MITHRILDAGGER}, {"Adamantine Dagger", ADAMANTINEDAGGER}
    };
    
    Monster* generateMonster(int type);
    Item* generateItem(ITEMS type);
    RoomObject* generateRoomObj(int type);
    
    
};

#endif /* Generation_h */
