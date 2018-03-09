/*******************************************************************
 
 Specification file for the Item class.
 
 */

#ifndef Item_h
#define Item_h

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
    virtual string description();
    virtual ~PortalGem(){};
};

class Ruby : public PortalGem
{
public:
    string name();
    string description();
    ~Ruby(){}
};

class Sapphire : public PortalGem
{
public:
    string name();
    string description();
    ~Sapphire(){}
};

class Emerald : public PortalGem
{
public:
    string name();
    string description();
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
    int getValue();
    Potion(int n) : value(n){}
    virtual ~Potion(){}
};

//Heals player, increasing their current health to at most the value of
//their max health2
class HealthPotion : public Potion
{
public:
    string name();
    string description();
    HealthPotion() : Potion(15){};
    ~HealthPotion(){}
};

//Permanently increases player's max health
class MaxHealthPotion : public Potion
{
public:
    string name();
    string description();
    MaxHealthPotion() : Potion(5){};
    ~MaxHealthPotion(){}
};

//Permanently increases player's strength
class StrengthPotion : public Potion
{
public:
    string name();
    string description();
    StrengthPotion() : Potion(1){};
    ~StrengthPotion(){}
};

//Permanently increases player's intelligence
class IntPotion : public Potion
{
public:
    string name();
    string description();
    IntPotion() : Potion(1){};
    ~IntPotion(){}
};

//Permanently increases player's luck
class LuckPotion : public Potion
{
public:
    string name();
    string description();
    LuckPotion() : Potion(1){};
    ~LuckPotion(){}
};

//Instantly kills an enemy
class KillScroll : public Item
{
public:
    string name();
    string description();
    ~KillScroll(){}
};

class Equipment : public Item
{
protected:
    int value;
public:
    int getValue();
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
    virtual string name();
    virtual string description();
    Iron() : Material(1){}
    virtual ~Iron(){}
};

class Steel : public Material
{
public:
    virtual string name();
    virtual string description();
    Steel() : Material(2){}
    virtual ~Steel(){}
};

class Mithril : public Material
{
public:
    virtual string name();
    virtual string description();
    Mithril() : Material(3){}
    virtual ~Mithril(){}
};

class Adamantine : public Material
{
public:
    virtual string name();
    virtual string description();
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
    virtual string name();
    virtual string description();
    Helmet(int n) : Equipment(n * 4){}
    virtual ~Helmet(){}
};

//Abstract class for torso armor
class Armor : public Equipment
{
public:
    virtual string name();
    virtual string description();
    Armor(int n) : Equipment(n * 6){}
    virtual ~Armor(){}
};

//Abstract class for lower body armor
class Greaves : public Equipment
{
public:
    virtual string name();
    virtual string description();
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
    virtual string name();
    virtual string description();
    Sword(int n) : Weapon(n * 3){}
    virtual ~Sword(){}
};

class Dagger : public Weapon
{
public:
    virtual string name();
    virtual string description();
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
    string name();
    string description();
    IronHelmet() : Iron(), Helmet(matValue){}
    ~IronHelmet(){}
};

class SteelHelmet : public Steel, public Helmet
{
public:
    string name();
    string description();
    SteelHelmet() : Steel(), Helmet(matValue){}
    ~SteelHelmet(){}
};

class MithrilHelmet : public Mithril, public Helmet
{
public:
    string name();
    string description();
    MithrilHelmet() : Mithril(), Helmet(matValue){}
    ~MithrilHelmet(){}
};

class AdamantineHelmet : public Adamantine, public Helmet
{
public:
    string name();
    string description();
    AdamantineHelmet() : Adamantine(), Helmet(matValue){}
    ~AdamantineHelmet(){}
};

class IronArmor : public Iron, public Armor
{
public:
    string name();
    string description();
    IronArmor() : Iron(), Armor(matValue){}
    ~IronArmor(){}
};

class SteelArmor : public Steel, public Armor
{
public:
    string name();
    string description();
    SteelArmor() : Steel(), Armor(matValue){}
    ~SteelArmor(){}
};

class MithrilArmor : public Mithril, public Armor
{
public:
    string name();
    string description();
    MithrilArmor() : Mithril(), Armor(matValue){}
    ~MithrilArmor(){}
};

class AdamantineArmor : public Adamantine, public Armor
{
public:
    string name();
    string description();
    AdamantineArmor() : Adamantine(), Armor(matValue){}
    ~AdamantineArmor(){}
};

class IronGreaves : public Iron, public Greaves
{
public:
    string name();
    string description();
    IronGreaves() : Iron(), Greaves(matValue){}
    ~IronGreaves(){}
};

class SteelGreaves : public Steel, public Greaves
{
public:
    string name();
    string description();
    SteelGreaves() : Steel(), Greaves(matValue){}
    ~SteelGreaves(){}
};

class MithrilGreaves : public Mithril, public Greaves
{
public:
    string name();
    string description();
    MithrilGreaves() : Mithril(), Greaves(matValue){}
    ~MithrilGreaves(){}
};

class AdamantineGreaves : public Adamantine, public Greaves
{
public:
    string name();
    string description();
    AdamantineGreaves() : Adamantine(), Greaves(matValue){}
    ~AdamantineGreaves(){}
};

class IronSword : public Iron, public Sword
{
public:
    string name();
    string description();
    IronSword() : Iron(), Sword(matValue){}
    ~IronSword(){}
};

class SteelSword : public Steel, public Sword
{
public:
    string name();
    string description();
    SteelSword() : Steel(), Sword(matValue){}
    ~SteelSword(){}
};

class MithrilSword : public Mithril, public Sword
{
public:
    string name();
    string description();
    MithrilSword() : Mithril(), Sword(matValue){}
    ~MithrilSword(){}
};

class AdamantineSword : public Adamantine, public Sword
{
public:
    string name();
    string description();
    AdamantineSword() : Adamantine(), Sword(matValue){}
    ~AdamantineSword(){}
};

class IronDagger : public Iron, public Dagger
{
public:
    string name();
    string description();
    IronDagger() : Iron(), Dagger(matValue){}
    ~IronDagger(){}
};

class SteelDagger : public Steel, public Dagger
{
public:
    string name();
    string description();
    SteelDagger() : Steel(), Dagger(matValue){}
    ~SteelDagger(){}
};

class MithrilDagger : public Mithril, public Dagger
{
public:
    string name();
    string description();
    MithrilDagger() : Mithril(), Dagger(matValue){}
    ~MithrilDagger(){}
};

class AdamantineDagger : public Adamantine, public Dagger
{
public:
    string name();
    string description();
    AdamantineDagger() : Adamantine(), Dagger(matValue){}
    ~AdamantineDagger(){}
};




#endif
