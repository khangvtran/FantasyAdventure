/*
 
 Specification file for the Item class.
 
 */

#ifndef Item_h
#define Item_h

#include <iostream>
#include <string>
using namespace std;

class Item
{
public:
    virtual string name() = 0;
    virtual string description() = 0;
    virtual ~Item() {}
};

/*******************************************************************
 The following three classes are Portal Gems, required to be in the
 character's inventory in order to beat the game
 */
class Ruby : public Item
{
public:
    string name(){return "Ruby";}
    string description(){return "";}
};

class Sapphire : public Item
{
public:
    string name(){return "Sapphire";}
    string description(){return "";}
};

class Emerald : public Item
{
public:
    string name(){return "Emerald";}
    string description(){return "";}
};

/*******************************************************************
 The following classes are all single-use consumables
 */
class Potion : public Item
{
protected:
    //the value that will be used to determine how much the
    //potion heals or buffs
    int value;
public:
    int getValue(){return value;}
    Potion(int n) : value(n){}
};

//Heals player, increasing their current health to at most the value of
//their max health2
class HealthPotion : public Potion
{
public:
    string name(){return "Health Potion";}
    string description(){return "";}
    HealthPotion() : Potion(15){};
};

//Permanently increases player's max health
class MaxHealthPotion : public Potion
{
public:
    string name(){return "Max Health Potion";}
    string description(){return "";}
    MaxHealthPotion() : Potion(5){};
};

//Permanently increases player's strength
class StrengthPotion : public Potion
{
public:
    string name(){return "Strength Potion";}
    string description(){return "";}
    StrengthPotion() : Potion(1){};
};

//Permanently increases player's intelligence
class IntPotion : public Potion
{
public:
    string name(){return "Intelligence Potion";}
    string description(){return "";}
    IntPotion() : Potion(1){};
};

//Permanently increases player's luck
class LuckPotion : public Potion
{
public:
    string name(){return "Luck Potion";}
    string description(){return "";}
    LuckPotion() : Potion(1){};
};

//Instantly kills an enemy
class KillScroll : public Item
{
public:
    string name(){return "Kill Scroll";}
    string description(){return "";}
};

class Equipment : public Item
{
protected:
    int value;
public:
    int getvalue(){return value;}
    Equipment(int n) : value(n){}
};

/********************************************************************
 Abstract base class for equipment materials, which determine
 the strength of weapons and armor.  In order of weakest to strongest:
 Iron < Steel < Mithril < Adamantine
 */
class Material
{
protected:
    int matValue;
public:
    Material(int n) : matValue(n){}
};

class Iron : public Material
{
public:
    virtual string name(){return "Iron";}
    Iron() : Material(1){}
};

class Steel : public Material
{
public:
    virtual string name(){return "Steel";}
    Steel() : Material(2){}
};

class Mithril : public Material
{
public:
    virtual string name(){return "Mithril";}
    Mithril() : Material(3){}
};

class Adamantine : public Material
{
public:
    virtual string name(){return "Adamantine";}
    Adamantine() : Material(4){}
};

/********************************************************************
 Abstract classes for weapon and armor types
 */
//Abstract class for head armor
class Helmet : public Equipment
{
public:
    virtual string name(){return "Helmet";}
    Helmet(int n) : Equipment(n * 4){}
};

//Abstract class for torso armor
class Armor : public Equipment
{
public:
    virtual string name(){return "Armor";}
    Armor(int n) : Equipment(n * 6){}
};

//Abstract class for lower body armor
class Greaves : public Equipment
{
public:
    virtual string name(){return "Greaves";}
    Greaves(int n) : Equipment(n * 5){}
};

//Abstract class for weapons, inherited from by both Sword and Dagger
class Weapon : public Equipment
{
public:
    Weapon(int n) : Equipment(n){};
};

class Sword : public Weapon
{
public:
    virtual string name(){return "Sword";}
    Sword(int n) : Weapon(n * 3){}
};

class Dagger : public Weapon
{
public:
    virtual string name(){return "Dagger";}
    Dagger(int n) : Weapon(n * 2){}
};

/********************************************************************
 Everything after this point is a fully derived, non-abstract class
 Each type of armor and weapon has 4 versions of different strengths
 determined by the Material classes.
 */
class IronHelmet : public Iron, public Helmet
{
public:
    string name(){return Iron::name() + " " + Helmet::name();}
    string description(){return "";}
    int getValue(){return value;}
    IronHelmet() : Iron(), Helmet(matValue){}
};

class SteelHelmet : public Steel, public Helmet
{
public:
    string name(){return Steel::name() + " " + Helmet::name();}
    string description(){return "";}
    int getValue(){return value;}
    SteelHelmet() : Steel(), Helmet(matValue){}
};

class MithrilHelmet : public Mithril, public Helmet
{
public:
    string name(){return Mithril::name() + " " + Helmet::name();}
    string description(){return "";}
    int getValue(){return value;}
    MithrilHelmet() : Mithril(), Helmet(matValue){}
};

class AdamantineHelmet : public Adamantine, public Helmet
{
public:
    string name(){return Adamantine::name() + " " + Helmet::name();}
    string description(){return "";}
    int getValue(){return value;}
    AdamantineHelmet() : Adamantine(), Helmet(matValue){}
};

class IronArmor : public Iron, public Armor
{
public:
    string name(){return Iron::name() + " " + Armor::name();}
    string description(){return "";}
    int getValue(){return value;}
    IronArmor() : Iron(), Armor(matValue){}
};

class SteelArmor : public Steel, public Armor
{
public:
    string name(){return Steel::name() + " " + Armor::name();}
    string description(){return "";}
    int getValue(){return value;}
    SteelArmor() : Steel(), Armor(matValue){}
};

class MithrilArmor : public Mithril, public Armor
{
public:
    string name(){return Mithril::name() + " " + Armor::name();}
    string description(){return "";}
    int getValue(){return value;}
    MithrilArmor() : Mithril(), Armor(matValue){}
};

class AdamantineArmor : public Adamantine, public Armor
{
public:
    string name(){return Adamantine::name() + " " + Armor::name();}
    string description(){return "";}
    int getValue(){return value;}
    AdamantineArmor() : Adamantine(), Armor(matValue){}
};

class IronGreaves : public Iron, public Greaves
{
public:
    string name(){return Iron::name() + " " + Greaves::name();}
    string description(){return "";}
    int getValue(){return value;}
    IronGreaves() : Iron(), Greaves(matValue){}
};

class SteelGreaves : public Steel, public Greaves
{
public:
    string name(){return Steel::name() + " " + Greaves::name();}
    string description(){return "";}
    int getValue(){return value;}
    SteelGreaves() : Steel(), Greaves(matValue){}
};

class MithrilGreaves : public Mithril, public Greaves
{
public:
    string name(){return Mithril::name() + " " + Greaves::name();}
    string description(){return "";}
    int getValue(){return value;}
    MithrilGreaves() : Mithril(), Greaves(matValue){}
};

class AdamantineGreaves : public Adamantine, public Greaves
{
public:
    string name(){return Adamantine::name() + " " + Greaves::name();}
    string description(){return "";}
    int getValue(){return value;}
    AdamantineGreaves() : Adamantine(), Greaves(matValue){}
};

class IronSword : public Iron, public Sword
{
public:
    string name(){return Iron::name() + " " + Sword::name();}
    string description(){return "";}
    int getValue(){return value;}
    IronSword() : Iron(), Sword(matValue){}
};

class SteelSword : public Steel, public Sword
{
public:
    string name(){return Steel::name() + " " + Sword::name();}
    string description(){return "";}
    int getValue(){return value;}
    SteelSword() : Steel(), Sword(matValue){}
};

class MithrilSword : public Mithril, public Sword
{
public:
    string name(){return Mithril::name() + " " + Sword::name();}
    string description(){return "";}
    int getValue(){return value;}
    MithrilSword() : Mithril(), Sword(matValue){}
};

class AdamantineSword : public Adamantine, public Sword
{
public:
    string name(){return Adamantine::name() + " " + Sword::name();}
    string description(){return "";}
    int getValue(){return value;}
    AdamantineSword() : Adamantine(), Sword(matValue){}
};

class IronDagger : public Iron, public Dagger
{
public:
    string name(){return Iron::name() + " " + Dagger::name();}
    string description(){return "";}
    int getValue(){return value;}
    IronDagger() : Iron(), Dagger(matValue){}
};

class SteelDagger : public Steel, public Dagger
{
public:
    string name(){return Steel::name() + " " + Dagger::name();}
    string description(){return "";}
    int getValue(){return value;}
    SteelDagger() : Steel(), Dagger(matValue){}
};

class MithrilDagger : public Mithril, public Dagger
{
public:
    string name(){return Mithril::name() + " " + Dagger::name();}
    string description(){return "";}
    int getValue(){return value;}
    MithrilDagger() : Mithril(), Dagger(matValue){}
};

class AdamantineDagger : public Adamantine, public Dagger
{
public:
    string name(){return Adamantine::name() + " " + Dagger::name();}
    string description(){return "";}
    int getValue(){return value;}
    AdamantineDagger() : Adamantine(), Dagger(matValue){}
};




#endif

