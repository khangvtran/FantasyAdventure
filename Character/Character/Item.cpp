#include <string>
#include "Item.h"


int Potion::getValue()
{
    return value;
}

int Equipment::getValue()
{
    return value;
}

/*******************************************************************
 Abstract class name() functions
 *******************************************************************/

/*Materials*/
std::string Iron::name()
{
    return "iron";
}

std::string Steel::name()
{
    return "steel";
}

std::string Mithril::name()
{
    return "mithril";
}

std::string Adamantine::name()
{
    return "adamantine";
}

/*Equipment*/
std::string Helmet::name()
{
    return "helmet";
}

std::string Armor::name()
{
    return "armor";
}

std::string Greaves::name()
{
    return "greaves";
}

std::string Sword::name()
{
    return "sword";
}

std::string Dagger::name()
{
    return "dagger";
}

/*******************************************************************
 Derived class name() functions
 *******************************************************************/

/*Portal Gems*/
std::string Ruby::name()
{
    return "ruby";
}

std::string Sapphire::name()
{
    return "sapphire";
}

std::string Emerald::name()
{
    return "emerald";
}

/*Potions*/
std::string HealthPotion::name()
{
    return "health potion";
}

std::string MaxHealthPotion::name()
{
    return "max health potion";
}

std::string StrengthPotion::name()
{
    return "strength potion";
}

std::string IntPotion::name()
{
    return "intelligence potion";
}

std::string LuckPotion::name()
{
    return "luck potion";
}

/*Other*/
std::string KillScroll::name()
{
    return "kill scroll";
}

/*Equipment*/
std::string IronHelmet::name()
{
    return Iron::name() + " " + Helmet::name();
}

std::string SteelHelmet::name()
{
    return Steel::name() + " " + Helmet::name();
}

std::string MithrilHelmet::name()
{
    return Mithril::name() + " " + Helmet::name();
}

std::string AdamantineHelmet::name()
{
    return Adamantine::name() + " " + Helmet::name();
}

std::string IronArmor::name()
{
    return Iron::name() + " " + Armor::name();
}

std::string SteelArmor::name()
{
    return Steel::name() + " " + Armor::name();
}

std::string MithrilArmor::name()
{
    return Mithril::name() + " " + Armor::name();
}

std::string AdamantineArmor::name()
{
    return Adamantine::name() + " " + Armor::name();
}

std::string IronGreaves::name()
{
    return Iron::name() + " " + Greaves::name();
}

std::string SteelGreaves::name()
{
    return Steel::name() + " " + Greaves::name();
}

std::string MithrilGreaves::name()
{
    return Mithril::name() + " " + Greaves::name();
}

std::string AdamantineGreaves::name()
{
    return Adamantine::name() + " " + Greaves::name();
}

std::string IronSword::name()
{
    return Iron::name() + " " + Sword::name();
}

std::string SteelSword::name()
{
    return Steel::name() + " " + Sword::name();
}

std::string MithrilSword::name()
{
    return Mithril::name() + " " + Sword::name();
}

std::string AdamantineSword::name()
{
    return Adamantine::name() + " " + Sword::name();
}

std::string IronDagger::name()
{
    return Iron::name() + " " + Dagger::name();
}

std::string SteelDagger::name()
{
    return Steel::name() + " " + Dagger::name();
}

std::string MithrilDagger::name()
{
    return Mithril::name() + " " + Dagger::name();
}

std::string AdamantineDagger::name()
{
    return Adamantine::name() + " " + Dagger::name();
}

/*******************************************************************
 Abstract class description() functions
 */

std::string PortalGem::description()
{
    return "gem that seems to sparkle with an inner light.";
}

/*Materials*/
std::string Iron::description()
{
    return "iron, the most basic material.";
}

std::string Steel::description()
{
    return "steel, stronger than iron.";
}

std::string Mithril::description()
{
    return "mithril, stronger than iron or steel.";
}

std::string Adamantine::description()
{
    return "adamantine, the strongest material.";
}

/*Equipment*/
std::string Helmet::description()
{
    return "A helmet made from";
}

std::string Armor::description()
{
    return "Armor made from";
}

std::string Greaves::description()
{
    return "Greaves made from";
}

std::string Sword::description()
{
    return "A sword made from";
}

std::string Dagger::description()
{
    return "A dagger made from";
}

/*******************************************************************
 Derived class description() functions
 *******************************************************************/

/*Portal Gems*/
std::string Ruby::description()
{
    return "A large, blood red " + PortalGem::description();
}

std::string Sapphire::description()
{
    return "A large, deep blue " + PortalGem::description();
}

std::string Emerald::description()
{
    return "A large, bright green " + PortalGem::description();
}

/*Potions*/
std::string HealthPotion::description()
{
    return "A flask of red liquid that will restore your health.";
}

std::string MaxHealthPotion::description()
{
    return "A flask of purple liquid that will increase your maximum health.";
}

std::string StrengthPotion::description()
{
    return "A flask of yellow liquid that will strengthen you.";
}

std::string IntPotion::description()
{
    return "A flask of blue liquid that will sharpen your wits.";
}

std::string LuckPotion::description()
{
    return "A flask of opaque white liquid that will increase your luck.";
}

/*Other*/
std::string KillScroll::description()
{
    return "A yellowing, tattered scroll inscribed with eldritch runes that will kill any monster when read.";
}

/*Equipment*/
std::string IronHelmet::description()
{
    return Helmet::description() + " " + Iron::description();
}

std::string SteelHelmet::description()
{
    return Helmet::description() + " " + Steel::description();
}

std::string MithrilHelmet::description()
{
    return Helmet::description() + " " + Mithril::description();
}

std::string AdamantineHelmet::description()
{
    return Helmet::description() + " " + Adamantine::description();
}

std::string IronArmor::description()
{
    return Armor::description() + " " + Iron::description();
}

std::string SteelArmor::description()
{
    return Armor::description() + " " + Steel::description();
}

std::string MithrilArmor::description()
{
    return Armor::description() + " " + Mithril::description();
}

std::string AdamantineArmor::description()
{
    return Armor::description() + " " + Adamantine::description();
}

std::string IronGreaves::description()
{
    return Greaves::description() + " " + Iron::description();
}

std::string SteelGreaves::description()
{
    return Greaves::description() + " " + Steel::description();
}

std::string MithrilGreaves::description()
{
    return Greaves::description() + " " + Mithril::description();
}

std::string AdamantineGreaves::description()
{
    return Greaves::description() + " " + Adamantine::description();
}

std::string IronSword::description()
{
    return Sword::description() + " " + Iron::description();
}

std::string SteelSword::description()
{
    return Sword::description() + " " + Steel::description();
}

std::string MithrilSword::description()
{
    return Sword::description() + " " + Mithril::description();
}

std::string AdamantineSword::description()
{
    return Sword::description() + " " + Adamantine::description();
}

std::string IronDagger::description()
{
    return Dagger::description() + " " + Iron::description();
}

std::string SteelDagger::description()
{
    return Dagger::description() + " " + Steel::description();
}

std::string MithrilDagger::description()
{
    return Dagger::description() + " " + Mithril::description();
}

std::string AdamantineDagger::description()
{
    return Dagger::description() + " " + Adamantine::description();
}
