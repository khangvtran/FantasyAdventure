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
    virtual ~Item(){}
};

/*******************************************************************
 The following three classes are Portal Gems, required to be in the
 character's inventory in order to beat the game
 */

class PortalGem : public Item
{
public:
    virtual string description(){return "gem that seems to sparkle with an inner light.";}
    virtual ~PortalGem(){};
};

class Ruby : public PortalGem
{
public:
    string name(){return "Ruby";}
    string description(){return "A large, blood red " + PortalGem::description();}
    ~Ruby(){}
};

class Sapphire : public PortalGem
{
public:
    string name(){return "Sapphire";}
    string description(){return "A large, deep blue " + PortalGem::description();}
    ~Sapphire(){}
};

class Emerald : public PortalGem
{
public:
    string name(){return "Emerald";}
    string description(){return "A large, bright green " + PortalGem::description();}
    ~Emerald(){}
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
    virtual ~Potion(){}
};

//Heals player, increasing their current health to at most the value of
//their max health2
class HealthPotion : public Potion
{
public:
    string name(){return "Health Potion";}
    string description(){return "A flask of red liquid that will restore your health.";}
    HealthPotion() : Potion(15){};
    ~HealthPotion(){}
};

//Permanently increases player's max health
class MaxHealthPotion : public Potion
{
public:
    string name(){return "Max Health Potion";}
    string description(){return "A flask of purple liquid that will increase your maximum health.";}
    MaxHealthPotion() : Potion(5){};
    ~MaxHealthPotion(){}
};

//Permanently increases player's strength
class StrengthPotion : public Potion
{
public:
    string name(){return "Strength Potion";}
    string description(){return "A flask of yellow liquid that will strengthen you.";}
    StrengthPotion() : Potion(1){};
    ~StrengthPotion(){}
};

//Permanently increases player's intelligence
class IntPotion : public Potion
{
public:
    string name(){return "Intelligence Potion";}
    string description(){return "A flask of blue liquid that will sharpen your wits.";}
    IntPotion() : Potion(1){};
    ~IntPotion(){}
};

//Permanently increases player's luck
class LuckPotion : public Potion
{
public:
    string name(){return "Luck Potion";}
    string description(){return "A flask of opaque white liquid that will increase your luck.";}
    LuckPotion() : Potion(1){};
    ~LuckPotion(){}
};

//Instantly kills an enemy
class KillScroll : public Item
{
public:
    string name(){return "Kill Scroll";}
    string description(){return "A yellowing, tattered scroll inscribed with eldritch runes that will kill any monster when read.";}
    ~KillScroll(){}
};

class Equipment : public Item
{
protected:
    int value;
public:
    int getvalue(){return value;}
    Equipment(int n) : value(n){}
    virtual ~Equipment(){}
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
    virtual ~Material(){}
};

class Iron : public Material
{
public:
    virtual string name(){return "Iron";}
    virtual string description(){return "iron, the most basic material.";}
    Iron() : Material(1){}
    virtual ~Iron(){}
};

class Steel : public Material
{
public:
    virtual string name(){return "Steel";}
    virtual string description(){return "steel, stronger than iron.";}
    Steel() : Material(2){}
    virtual ~Steel(){}
};

class Mithril : public Material
{
public:
    virtual string name(){return "Mithril";}
    virtual string description(){return "mithril, stronger than iron or steel.";}
    Mithril() : Material(3){}
    virtual ~Mithril(){}
};

class Adamantine : public Material
{
public:
    virtual string name(){return "Adamantine";}
    virtual string description(){return "adamantine, the strongest material.";}
    Adamantine() : Material(4){}
    virtual ~Adamantine(){}
};

/********************************************************************
 Abstract classes for weapon and armor types
 */
//Abstract class for head armor
class Helmet : public Equipment
{
public:
    virtual string name(){return "Helmet";}
    virtual string description(){return "A helmet made from";}
    Helmet(int n) : Equipment(n * 4){}
    virtual ~Helmet(){}
};

//Abstract class for torso armor
class Armor : public Equipment
{
public:
    virtual string name(){return "Armor";}
    virtual string description(){return "Armor made from";}
    Armor(int n) : Equipment(n * 6){}
    virtual ~Armor(){}
};

//Abstract class for lower body armor
class Greaves : public Equipment
{
public:
    virtual string name(){return "Greaves";}
    virtual string description(){return "Greaves made from";}
    Greaves(int n) : Equipment(n * 5){}
    virtual ~Greaves(){}
};

//Abstract class for weapons, inherited from by both Sword and Dagger
class Weapon : public Equipment
{
public:
    Weapon(int n) : Equipment(n){};
    virtual ~Weapon(){}
};

class Sword : public Weapon
{
public:
    virtual string name(){return "Sword";}
    virtual string description(){return "A sword made from";}
    Sword(int n) : Weapon(n * 3){}
    virtual ~Sword(){}
};

class Dagger : public Weapon
{
public:
    virtual string name(){return "Dagger";}
    virtual string description(){return "A dagger made from";}
    Dagger(int n) : Weapon(n * 2){}
    virtual ~Dagger(){}
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
    string description(){return Helmet::description() + " " + Iron::description();}
    int getValue(){return value;}
    IronHelmet() : Iron(), Helmet(matValue){}
    ~IronHelmet(){}
};

class SteelHelmet : public Steel, public Helmet
{
public:
    string name(){return Steel::name() + " " + Helmet::name();}
    string description(){return Helmet::description() + " " + Steel::description();}
    int getValue(){return value;}
    SteelHelmet() : Steel(), Helmet(matValue){}
    ~SteelHelmet(){}
};

class MithrilHelmet : public Mithril, public Helmet
{
public:
    string name(){return Mithril::name() + " " + Helmet::name();}
    string description(){return Helmet::description() + " " + Mithril::description();}
    int getValue(){return value;}
    MithrilHelmet() : Mithril(), Helmet(matValue){}
    ~MithrilHelmet(){}
};

class AdamantineHelmet : public Adamantine, public Helmet
{
public:
    string name(){return Adamantine::name() + " " + Helmet::name();}
    string description(){return Helmet::description() + " " + Adamantine::description();}
    int getValue(){return value;}
    AdamantineHelmet() : Adamantine(), Helmet(matValue){}
    ~AdamantineHelmet(){}
};

class IronArmor : public Iron, public Armor
{
public:
    string name(){return Iron::name() + " " + Armor::name();}
    string description(){return Armor::description() + " " + Iron::description();}
    int getValue(){return value;}
    IronArmor() : Iron(), Armor(matValue){}
    ~IronArmor(){}
};

class SteelArmor : public Steel, public Armor
{
public:
    string name(){return Steel::name() + " " + Armor::name();}
    string description(){return Armor::description() + " " + Steel::description();}
    int getValue(){return value;}
    SteelArmor() : Steel(), Armor(matValue){}
    ~SteelArmor(){}
};

class MithrilArmor : public Mithril, public Armor
{
public:
    string name(){return Mithril::name() + " " + Armor::name();}
    string description(){return Armor::description() + " " + Mithril::description();}
    int getValue(){return value;}
    MithrilArmor() : Mithril(), Armor(matValue){}
    ~MithrilArmor(){}
};

class AdamantineArmor : public Adamantine, public Armor
{
public:
    string name(){return Adamantine::name() + " " + Armor::name();}
    string description(){return Armor::description() + " " + Adamantine::description();}
    int getValue(){return value;}
    AdamantineArmor() : Adamantine(), Armor(matValue){}
    ~AdamantineArmor(){}
};

class IronGreaves : public Iron, public Greaves
{
public:
    string name(){return Iron::name() + " " + Greaves::name();}
    string description(){return Greaves::description() + " " + Iron::description();}
    int getValue(){return value;}
    IronGreaves() : Iron(), Greaves(matValue){}
    ~IronGreaves(){}
};

class SteelGreaves : public Steel, public Greaves
{
public:
    string name(){return Steel::name() + " " + Greaves::name();}
    string description(){return Greaves::description() + " " + Steel::description();}
    int getValue(){return value;}
    SteelGreaves() : Steel(), Greaves(matValue){}
    ~SteelGreaves(){}
};

class MithrilGreaves : public Mithril, public Greaves
{
public:
    string name(){return Mithril::name() + " " + Greaves::name();}
    string description(){return Greaves::description() + " " + Mithril::description();}
    int getValue(){return value;}
    MithrilGreaves() : Mithril(), Greaves(matValue){}
    ~MithrilGreaves(){}
};

class AdamantineGreaves : public Adamantine, public Greaves
{
public:
    string name(){return Adamantine::name() + " " + Greaves::name();}
    string description(){return Greaves::description() + " " + Adamantine::description();}
    int getValue(){return value;}
    AdamantineGreaves() : Adamantine(), Greaves(matValue){}
    ~AdamantineGreaves(){}
};

class IronSword : public Iron, public Sword
{
public:
    string name(){return Iron::name() + " " + Sword::name();}
    string description(){return Sword::description() + " " + Iron::description();}
    int getValue(){return value;}
    IronSword() : Iron(), Sword(matValue){}
    ~IronSword(){}
};

class SteelSword : public Steel, public Sword
{
public:
    string name(){return Steel::name() + " " + Sword::name();}
    string description(){return Sword::description() + " " + Steel::description();}
    int getValue(){return value;}
    SteelSword() : Steel(), Sword(matValue){}
    ~SteelSword(){}
};

class MithrilSword : public Mithril, public Sword
{
public:
    string name(){return Mithril::name() + " " + Sword::name();}
    string description(){return Sword::description() + " " + Mithril::description();}
    int getValue(){return value;}
    MithrilSword() : Mithril(), Sword(matValue){}
    ~MithrilSword(){}
};

class AdamantineSword : public Adamantine, public Sword
{
public:
    string name(){return Adamantine::name() + " " + Sword::name();}
    string description(){return Sword::description() + " " + Adamantine::description();}
    int getValue(){return value;}
    AdamantineSword() : Adamantine(), Sword(matValue){}
    ~AdamantineSword(){}
};

class IronDagger : public Iron, public Dagger
{
public:
    string name(){return Iron::name() + " " + Dagger::name();}
    string description(){return Dagger::description() + " " + Iron::description();}
    int getValue(){return value;}
    IronDagger() : Iron(), Dagger(matValue){}
    ~IronDagger(){}
};

class SteelDagger : public Steel, public Dagger
{
public:
    string name(){return Steel::name() + " " + Dagger::name();}
    string description(){return Dagger::description() + " " + Steel::description();}
    int getValue(){return value;}
    SteelDagger() : Steel(), Dagger(matValue){}
    ~SteelDagger(){}
};

class MithrilDagger : public Mithril, public Dagger
{
public:
    string name(){return Mithril::name() + " " + Dagger::name();}
    string description(){return Dagger::description() + " " + Mithril::description();}
    int getValue(){return value;}
    MithrilDagger() : Mithril(), Dagger(matValue){}
    ~MithrilDagger(){}
};

class AdamantineDagger : public Adamantine, public Dagger
{
public:
    string name(){return Adamantine::name() + " " + Dagger::name();}
    string description(){return Dagger::description() + " " + Adamantine::description();}
    int getValue(){return value;}
    AdamantineDagger() : Adamantine(), Dagger(matValue){}
    ~AdamantineDagger(){}
};




#endif

