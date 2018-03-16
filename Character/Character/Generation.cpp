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
            std::cerr << "item this shouldn't happen" << std::endl;
            return nullptr;
        }
    }
}


Monster* Generation::generateMonster(MONSTERS type)
{
    switch(type)
    {
        case DRAGON:
            return new Dragon("dragon", "This giant fire-spewing three-headed winged monster looks strong and intimidating.\nIf he's really angry, he'll throw fireballs at you! Watch out!");
        case TITAN:
            return new Titan("titan", "This gigantic humanlike creature can crush you in no time. If you're not careful, he can deal you a critical hit!");
        case DRAGONBOSS:
            return new DragonBoss("dragon boss", "So you have found the biggest and scariest dragon in this dungeon that guards this place's treasures.\nOnly a few moments separate you from becoming rich and winning the fame and glory of a great warrior you came here for.\nThe only thing you have to do is face this bad-tempered oversized colossus\nRemember he can hurl fireballs your way and knock down any of your equipment.\nGood luck! Become a legend or become dinner!");
        default:
        {
            std::cerr << "monster this should not happen" << std::endl;
            return nullptr;
        }
    }
}

RoomObject* Generation::generateRoomObj(ROOMOBJ type)
{
    switch(type)
    {
        case BOOK:
            return new Book("book","This black leather book contains hints about how to win the game.");
        case FLARE:
            return new Flare("flare","You can use this flare to check what's inside four adjacent rooms!");
        case FOUNTAIN:
            return new Fountain("fountain","This fountain may help you recover or make you ill. Do you want to take the risk?");
        case MAP:
            return new Map("map", "You find this large map hanging on the wall.\nYou can use it to check where the gems, monsters, and treasure are.");
        case TREASURE:
            return new Treasure("treasure", "You have found your riches!\nIn front of you is a chest full of gold coins, gemstones and other valuables! You have successfully accomplished your mission.\nAll you have to do is activate the treasure.\n");
        default:
        {
            std::cerr << "roomobj this should not happen" << std::endl;
            return nullptr;
        }
    }
}

