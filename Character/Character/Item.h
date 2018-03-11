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
    string name() override;
    string description() override;
    ~Ruby(){}
};

class Sapphire : public PortalGem
{
public:
    string name() override;
    string description() override;
    ~Sapphire(){}
};

class Emerald : public PortalGem
{
public:
    string name() override;
    string description() override;
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
    string name() override;
    string description() override;
    HealthPotion() : Potion(15){};
    ~HealthPotion(){}
};

//Permanently increases player's max health
class MaxHealthPotion : public Potion
{
public:
    string name() override;
    string description() override;
    MaxHealthPotion() : Potion(5){};
    ~MaxHealthPotion(){}
};

//Permanently increases player's strength
class StrengthPotion : public Potion
{
public:
    string name() override;
    string description() override;
    StrengthPotion() : Potion(1){};
    ~StrengthPotion(){}
};

//Permanently increases player's intelligence
class IntPotion : public Potion
{
public:
    string name() override;
    string description() override;
    IntPotion() : Potion(1){};
    ~IntPotion(){}
};

//Permanently increases player's luck
class LuckPotion : public Potion
{
public:
    string name() override;
    string description() override;
    LuckPotion() : Potion(1){};
    ~LuckPotion(){}
};

//Instantly kills an enemy
class KillScroll : public Item
{
public:
    string name() override;
    string description() override;
    ~KillScroll(){}
};

class Equipment : public Item
{
protected:
    int value;
public:
    int getValue();
    virtual string name() = 0;
    virtual string description() = 0;
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
    virtual string name() = 0;
    virtual string description() = 0;
    virtual ~Material(){}
};

class Iron : public Material
{
public:
    Iron() : Material(1){}
    string name() override;
    string description() override;
    virtual ~Iron(){}
};

class Steel : public Material
{
public:
    string name() override;
    string description() override;
    Steel() : Material(2){}
    virtual ~Steel(){}
};

class Mithril : public Material
{
public:
    string name() override;
    string description() override;
    Mithril() : Material(3){}
    virtual ~Mithril(){}
};

class Adamantine : public Material
{
public:
    string name() override;
    string description() override;
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
    Helmet(int n) : Equipment(n * 4){}
    virtual string name();
    virtual string description();
    virtual ~Helmet(){}
};

//Abstract class for torso armor
class Armor : public Equipment
{
public:
    Armor(int n) : Equipment(n * 6){}
    virtual string name();
    virtual string description();
    virtual ~Armor(){}
};

//Abstract class for lower body armor
class Greaves : public Equipment
{
public:
    Greaves(int n) : Equipment(n * 5){}
    virtual string name();
    virtual string description();
    virtual ~Greaves(){}
};

//Abstract class for weapons, inherited from by both Sword and Dagger
class Weapon : public Equipment
{
public:
    Weapon(int n) : Equipment(n){};
    virtual string name() = 0;
    virtual string description() = 0;
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
    string name() override;
    string description() override;
    IronHelmet() : Iron(), Helmet(matValue){}
    ~IronHelmet(){}
};

class SteelHelmet : public Steel, public Helmet
{
public:
    string name() override;
    string description() override;
    SteelHelmet() : Steel(), Helmet(matValue){}
    ~SteelHelmet(){}
};

class MithrilHelmet : public Mithril, public Helmet
{
public:
    string name() override;
    string description() override;
    MithrilHelmet() : Mithril(), Helmet(matValue){}
    ~MithrilHelmet(){}
};

class AdamantineHelmet : public Adamantine, public Helmet
{
public:
    string name() override;
    string description() override;
    AdamantineHelmet() : Adamantine(), Helmet(matValue){}
    ~AdamantineHelmet(){}
};

class IronArmor : public Iron, public Armor
{
public:
    string name() override;
    string description() override;
    IronArmor() : Iron(), Armor(matValue){}
    ~IronArmor(){}
};

class SteelArmor : public Steel, public Armor
{
public:
    string name() override;
    string description() override;
    SteelArmor() : Steel(), Armor(matValue){}
    ~SteelArmor(){}
};

class MithrilArmor : public Mithril, public Armor
{
public:
    string name() override;
    string description() override;
    MithrilArmor() : Mithril(), Armor(matValue){}
    ~MithrilArmor(){}
};

class AdamantineArmor : public Adamantine, public Armor
{
public:
    string name() override;
    string description() override;
    AdamantineArmor() : Adamantine(), Armor(matValue){}
    ~AdamantineArmor(){}
};

class IronGreaves : public Iron, public Greaves
{
public:
    string name() override;
    string description() override;
    IronGreaves() : Iron(), Greaves(matValue){}
    ~IronGreaves(){}
};

class SteelGreaves : public Steel, public Greaves
{
public:
    string name() override;
    string description() override;
    SteelGreaves() : Steel(), Greaves(matValue){}
    ~SteelGreaves(){}
};

class MithrilGreaves : public Mithril, public Greaves
{
public:
    string name() override;
    string description() override;
    MithrilGreaves() : Mithril(), Greaves(matValue){}
    ~MithrilGreaves(){}
};

class AdamantineGreaves : public Adamantine, public Greaves
{
public:
    string name() override;
    string description() override;
    AdamantineGreaves() : Adamantine(), Greaves(matValue){}
    ~AdamantineGreaves(){}
};

class IronSword : public Iron, public Sword
{
public:
    string name() override;
    string description() override;
    IronSword() : Iron(), Sword(matValue){}
    ~IronSword(){}
};

class SteelSword : public Steel, public Sword
{
public:
    string name() override;
    string description() override;
    SteelSword() : Steel(), Sword(matValue){}
    ~SteelSword(){}
};

class MithrilSword : public Mithril, public Sword
{
public:
    string name() override;
    string description() override;
    MithrilSword() : Mithril(), Sword(matValue){}
    ~MithrilSword(){}
};

class AdamantineSword : public Adamantine, public Sword
{
public:
    string name() override;
    string description() override;
    AdamantineSword() : Adamantine(), Sword(matValue){}
    ~AdamantineSword(){}
};

class IronDagger : public Iron, public Dagger
{
public:
    string name() override;
    string description() override;
    IronDagger() : Iron(), Dagger(matValue){}
    ~IronDagger(){}
};

class SteelDagger : public Steel, public Dagger
{
public:
    string name() override;
    string description() override;
    SteelDagger() : Steel(), Dagger(matValue){}
    ~SteelDagger(){}
};

class MithrilDagger : public Mithril, public Dagger
{
public:
    string name() override;
    string description() override;
    MithrilDagger() : Mithril(), Dagger(matValue){}
    ~MithrilDagger(){}
};

class AdamantineDagger : public Adamantine, public Dagger
{
public:
    string name() override;
    string description() override;
    AdamantineDagger() : Adamantine(), Dagger(matValue){}
    ~AdamantineDagger(){}
};




#endif
