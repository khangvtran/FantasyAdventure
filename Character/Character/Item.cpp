#include <string>

#include "Item.h"

using namespace std;

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
 */

/*Materials*/
string Iron::name()
{
    return "iron";
}

string Steel::name()
{
    return "steel";
}

string Mithril::name()
{
    return "mithril";
}

string Adamantine::name()
{
    return "adamantine";
}

/*Equipment*/
string Helmet::name()
{
    return "helmet";
}

string Armor::name()
{
    return "armor";
}

string Greaves::name()
{
    return "greaves";
}

string Sword::name()
{
    return "sword";
}

string Dagger::name()
{
    return "dagger";
}

/*******************************************************************
 Derived class name() functions
 */

/*Portal Gems*/
string Ruby::name()
{
    return "ruby";
}

string Sapphire::name()
{
    return "sapphire";
}

string Emerald::name()
{
    return "emerald";
}

/*Potions*/
string HealthPotion::name()
{
    return "health potion";
}

string MaxHealthPotion::name()
{
    return "max health potion";
}

string StrengthPotion::name()
{
    return "strength potion";
}

string IntPotion::name()
{
    return "intelligence potion";
}

string LuckPotion::name()
{
    return "luck potion";
}

/*Other*/
string KillScroll::name()
{
    return "kill scroll";
}

/*Equipment*/
string IronHelmet::name()
{
    return Iron::name() + " " + Helmet::name();
}

string SteelHelmet::name()
{
    return Steel::name() + " " + Helmet::name();
}

string MithrilHelmet::name()
{
    return Mithril::name() + " " + Helmet::name();
}

string AdamantineHelmet::name()
{
    return Adamantine::name() + " " + Helmet::name();
}

string IronArmor::name()
{
    return Iron::name() + " " + Armor::name();
}

string SteelArmor::name()
{
    return Steel::name() + " " + Armor::name();
}

string MithrilArmor::name()
{
    return Mithril::name() + " " + Armor::name();
}

string AdamantineArmor::name()
{
    return Adamantine::name() + " " + Armor::name();
}

string IronGreaves::name()
{
    return Iron::name() + " " + Greaves::name();
}

string SteelGreaves::name()
{
    return Steel::name() + " " + Greaves::name();
}

string MithrilGreaves::name()
{
    return Mithril::name() + " " + Greaves::name();
}

string AdamantineGreaves::name()
{
    return Adamantine::name() + " " + Greaves::name();
}

string IronSword::name()
{
    return Iron::name() + " " + Sword::name();
}

string SteelSword::name()
{
    return Steel::name() + " " + Sword::name();
}

string MithrilSword::name()
{
    return Mithril::name() + " " + Sword::name();
}

string AdamantineSword::name()
{
    return Adamantine::name() + " " + Sword::name();
}

string IronDagger::name()
{
    return Iron::name() + " " + Dagger::name();
}

string SteelDagger::name()
{
    return Steel::name() + " " + Dagger::name();
}

string MithrilDagger::name()
{
    return Mithril::name() + " " + Dagger::name();
}

string AdamantineDagger::name()
{
    return Adamantine::name() + " " + Dagger::name();
}

/*******************************************************************
 Abstract class description() functions
 */

string PortalGem::description()
{
    return "gem that seems to sparkle with an inner light.";
}

/*Materials*/
string Iron::description()
{
    return "iron, the most basic material.";
}

string Steel::description()
{
    return "steel, stronger than iron.";
}

string Mithril::description()
{
    return "mithril, stronger than iron or steel.";
}

string Adamantine::description()
{
    return "adamantine, the strongest material.";
}

/*Equipment*/
string Helmet::description()
{
    return "A helmet made from";
}

string Armor::description()
{
    return "Armor made from";
}

string Greaves::description()
{
    return "Greaves made from";
}

string Sword::description()
{
    return "A sword made from";
}

string Dagger::description()
{
    return "A dagger made from";
}

/*******************************************************************
 Derived class description() functions
 */

/*Portal Gems*/
string Ruby::description()
{
    return "A large, blood red " + PortalGem::description();
}

string Sapphire::description()
{
    return "A large, deep blue " + PortalGem::description();
}

string Emerald::description()
{
    return "A large, bright green " + PortalGem::description();
}

/*Potions*/
string HealthPotion::description()
{
    return "A flask of red liquid that will restore your health.";
}

string MaxHealthPotion::description()
{
    return "A flask of purple liquid that will increase your maximum health.";
}

string StrengthPotion::description()
{
    return "A flask of yellow liquid that will strengthen you.";
}

string IntPotion::description()
{
    return "A flask of blue liquid that will sharpen your wits.";
}

string LuckPotion::description()
{
    return "A flask of opaque white liquid that will increase your luck.";
}

/*Other*/
string KillScroll::description()
{
    return "A yellowing, tattered scroll inscribed with eldritch runes that will kill any monster when read.";
}

/*Equipment*/
string IronHelmet::description()
{
    return Helmet::description() + " " + Iron::description();
}

string SteelHelmet::description()
{
    return Helmet::description() + " " + Steel::description();
}

string MithrilHelmet::description()
{
    return Helmet::description() + " " + Mithril::description();
}

string AdamantineHelmet::description()
{
    return Helmet::description() + " " + Adamantine::description();
}

string IronArmor::description()
{
    return Armor::description() + " " + Iron::description();
}

string SteelArmor::description()
{
    return Armor::description() + " " + Steel::description();
}

string MithrilArmor::description()
{
    return Armor::description() + " " + Mithril::description();
}

string AdamantineArmor::description()
{
    return Armor::description() + " " + Adamantine::description();
}

string IronGreaves::description()
{
    return Greaves::description() + " " + Iron::description();
}

string SteelGreaves::description()
{
    return Greaves::description() + " " + Steel::description();
}

string MithrilGreaves::description()
{
    return Greaves::description() + " " + Mithril::description();
}

string AdamantineGreaves::description()
{
    return Greaves::description() + " " + Adamantine::description();
}

string IronSword::description()
{
    return Sword::description() + " " + Iron::description();
}

string SteelSword::description()
{
    return Sword::description() + " " + Steel::description();
}

string MithrilSword::description()
{
    return Sword::description() + " " + Mithril::description();
}

string AdamantineSword::description()
{
    return Sword::description() + " " + Adamantine::description();
}

string IronDagger::description()
{
    return Dagger::description() + " " + Iron::description();
}

string SteelDagger::description()
{
    return Dagger::description() + " " + Steel::description();
}

string MithrilDagger::description()
{
    return Dagger::description() + " " + Mithril::description();
}

string AdamantineDagger::description()
{
    return Dagger::description() + " " + Adamantine::description();
}
