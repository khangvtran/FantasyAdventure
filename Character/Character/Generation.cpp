//
//  Generation.cpp
//  Character
//
//  Created by Joshua Kuan on 02/03/2018.
//  Copyright © 2018 Joshua Kuan. All rights reserved.
//

#include "Generation.h"


Item* Generation::generateItem(ITEMS type)
{
    switch(type)
    {
        /** Consumables **/
        case HEALTHPOTION:
            return new HealthPotion();
        case MAXHEALTHPOTION:
            return new MaxHealthPotion();
        case STRENGTHPOTION:
            return new StrengthPotion();
        case INTPOTION:
            return new IntPotion();
        case LUCKPOTION:
            return new LuckPotion();
        case KILLSCROLL:
            return new KillScroll();
            
        /** Equipment **/
        case IRONHELMET:
            return new IronHelmet();
        case STEELHELMET:
            return new SteelHelmet();
        case MITHRILHELMET:
            return new MithrilHelmet();
        case ADAMANTINEHELMET:
            return new AdamantineHelmet();
            
        case IRONARMOR:
            return new IronArmor();
        case STEELARMOR:
            return new SteelArmor();
        case MITHRILARMOR:
            return new MithrilArmor();
        case ADAMANTINEARMOR:
            return new AdamantineArmor();
            
        case IRONGREAVES:
            return new IronGreaves();
        case STEELGREAVES:
            return new SteelGreaves();
        case MITHRILGREAVES:
            return new MithrilGreaves();
        case ADAMANTINEGREAVES:
            return new AdamantineGreaves();
            
        /** Weapons **/
        case IRONSWORD:
            return new IronSword();
        case STEELSWORD:
            return new SteelSword();
        case MITHRILSWORD:
            return new MithrilSword();
        case ADAMANTINESWORD:
            return new AdamantineSword();
        case IRONDAGGER:
            return new IronDagger();
        case STEELDAGGER:
            return new SteelDagger();
        case MITHRILDAGGER:
            return new MithrilDagger();
        case ADAMANTINEDAGGER:
            return new AdamantineDagger();
            
        /** Non-Consumable Items **/
        case RUBY:
            return new Ruby();
        case EMERALD:
            return new Emerald();
        case SAPPHIRE:
            return new Sapphire();
        default:
        {
            cerr << "this shouldn't happen" << endl;
            return nullptr;
        }
    }
}


Monster* Generation::generateMonster(MONSTERS type, const string& name, const string& description)
{
    switch(type)
    {
        case DRAGON:
            return new Dragon(name, description);
        case TITAN:
            return new Titan(name, description);
        case DRAGONBOSS:
            return new DragonBoss(name, description);
        default:
        {
            cerr << "this should not happen" << endl;
            return nullptr;
        }
    }
}

RoomObject* Generation::generateRoomObj(ROOMOBJ type, const string& name, const string& description)
{
    switch(type)
    {
        case BOOK:
            return new Book(name,description);
        case FLARE:
            return new Flare(name,description);
        case FOUNTAIN:
            return new Fountain(name,description);
        case MAP:
            return new Map(name,description);
        case TREASURE:
            return new Treasure(name,description);
        default:
        {
            cerr << "this should not happen" << endl;
            return nullptr;
        }
    }
}
