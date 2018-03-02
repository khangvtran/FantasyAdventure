/*
 
 Specification file for the Monster class.
 
 Here is the hierarchy for the Monster calss:
 
                                            Monster
                                            /    \
                                           /      \
                                        Dragon    Titan
                                          \        /
                                           \      /
                                          DragonBoss
 
 Class Monster is an abstract base class that has two derived clases: Dragon and Titan.
 All monsters have a name, description, strength, health, luck and an indicator whether they are dead or alive
 as well as an attack function that is a pure virtual function overriden in each of the derived classes.
 Dragon contains an additional data member of vitality which is a random number from range 0-20.
 If dragon's vitality is > 10, the attack function will also include throwing fireballs, which
 augument monster's strength and luck by 1.5.
 Titan contains an additional data member of agility which is a random number from range 0-20.
 If titan's agility is > 10, the attack function will also include knocking down character's equipment.
 Both Dragon and Titan are virtual base classes.
 The DragonBoss class derives from both the Dragon and Titan. It contains its own attack method that
 makes it throw fireballs if its vitality is > 10 and causes the character to drop a piece of equipment
 if its agility is > 10.
 
 Summary:
 Monster - abstract base class
 Data:
 name   - monster's name
 description - monster's decription
 strength  - randomly assigned, unique to each derived monster class
 health - unique to each derived moster class
 luck - randomly assigned, unique to each derived monster class
 alive - flag inidcating if a monster is dead or alive
 
 Functions:
 Constructor
 Destructor
 Setters (setStrength, setHealth, setLuck)
 Getters (getName, getDescription, getStrength, getHealth, getLuck)
 attack - pure virtual function defined and overridden in derived classes
 getHitAccuracy - returns true if character hit or missed
 
 Dragon - class derived from Monster
 Data:
 int vitality - randomly generated
 
 Functions:
 Constructor
 Destructor
 SetVitality
 GetVitality
 attack - returns an int representing damage done to the character based on monster stats
 throwFireBalls - is called if Dragon's vitality is greater than 10, augumets Dragon's basestats used in the attack function
 
 Titan - class derived from Monster
 Data:
 int agility - randomly generated
 
 Functions:
 Constructor
 Destructor
 SetAgility
 GetAgility
 attack - returns an int representing damage done to the character based on monster stats
 knockDownEquipment - is called if Titan's agility is > 10, makes the Character drop a piece of equimpment (it can still be picked up)
 
 DragonBoss - class dervied from Dragon and Titan
 Functions:
 Constructor
 Destructor
 attack - returns an int representing damage done to the character based on monster stats
 
 */

#ifndef Monster_h
#define Monster_h

#include <iostream>
#include <string>
using namespace std;

class Monster
{
protected:
    string name;            //stores monster name
    string description;     //stores monster description
    double strength;           //stores monster's strength
    double health;             //stores monster's health
    double luck;               //stores monster's luck
    double alive;             //flag to indicate whether a monster is dead or alive
public:
    //Constructor
    /* Initializes monster data with starting values */
    Monster(string mName = "", string mDescription = "", double mStrength = 0, double mHealth = 0, double mLuck = 0, bool mAlive = true) : name(mName), description(mDescription), strength(mStrength), health(mHealth), luck(mLuck), alive(mAlive) { /*cout << "Monster ctor" << endl; */}
    
    //Destructor
    virtual ~Monster() { /* cout << "Monster destructor" << endl; */}
    
    //Setters
    /* Sets monster health */
    void setHealth(double mHealth)
    {
        health = mHealth;
        if (health <= 0)
        {
            alive = false;
        }
    }
    /* Sets monster strength */
    void setStrength(double mStrength)
    {
        strength = mStrength;
    }
    /* Sets monster luck */
    void setLuck(double mLuck)
    {
        luck = mLuck;
    }
    /* Sets monster alive status */
    void setAlive(bool mAlive)
    {
        alive = mAlive;
    }
    /* Modifies monster's health by subtracting the amount of damage.
       Returns true if the monster is still alive and false if he is dead. */
    bool modifyHealth(double mDamage)
    {
        health -= mDamage;
        if (health <= 0)
        {
            alive = false;
        }
        return alive;
    }
    
    //Getters
    /* Returns monster name */
    string getName() const
    {
        return name;
    }
    /* Returns monster description */
    string getDescription() const
    {
        return description;
    }
    /* Returns monster strength */
    double getStrength() const
    {
        return strength;
    }
    /* Returns monster health */
    double getHealth() const
    {
        return health;
    }
    /* Returns monster luck */
    double getLuck() const
    {
        return luck;
    }
    /* Returns if a monster is dead or alive */
    bool isAlive() const
    {
        return alive;
    }
    /* Returns true if monster attack was a hit and false if it was a miss */
    bool getHitAccuracy(double characterLuck) const;
    
    //Pure virtual functions
    /* Returns an int representing damage done to the character */
    virtual int attack(double characterLuck, bool& loseEquip) = 0;
    
};

class Dragon : virtual public Monster
{
protected:
    double vitality;
public:
    //Constructors
    /* Initializes dragon attributes to starting values */
    Dragon(string mName = "", string mDescription = "", double mStrength = 0, double mHealth = 0, double mLuck = 0, bool mAlive = true, double mVitality = 0) : Monster(mName, mDescription, mStrength, mHealth,  mLuck, mAlive), vitality(mVitality)
    {
        //cout << "Dragon ctor" << endl;
        //Set Dragon strength
        const int STRENGTH_MIN = 0;
        const int STRENGTH_MAX = 15;
        strength = (rand() % (STRENGTH_MAX - STRENGTH_MIN + 1) + STRENGTH_MIN);
        setStrength(strength);
        
        //Set Dragon health
        health = 50;
        setHealth(health);
        
        //Set Dragon luck
        const int LUCK_MIN = 0;
        const int LUCK_MAX = 15;
        luck = (rand() % (LUCK_MAX - LUCK_MIN + 1) + LUCK_MIN);
        setLuck(luck);
        
        //Set Dragon vitality
        const int VITALITY_MIN = 0;
        const int VITALITY_MAX = 20;
        vitality = (rand() % (VITALITY_MAX - VITALITY_MIN + 1) + VITALITY_MIN);
        setVitality(vitality);
    }
    
    /* Specialized constructor: Initializes Dragon's vitality - data not inherited from the Monster class */
    Dragon(double mVitality)
    {
        //cout << "Dragon ctor" << endl;
        
        //Set Dragon vitality
        const int VITALITY_MIN = 0;
        const int VITALITY_MAX = 20;
        vitality = (rand() % (VITALITY_MAX - VITALITY_MIN + 1) + VITALITY_MIN);
        setVitality(vitality);
    }
    
    //Destructor
    virtual ~Dragon() {}
    
    //Setters
    /* Sets Dragon vitality */
    void setVitality(double mVitality)
    {
        vitality = mVitality;
    }
    
    //Getters
    /* Returns Dragon vitality */
    double getVitality() const
    {
        return vitality;
    }
    
    //Pure virtual functions
    /* Returns an int representing damage done to the character */
    virtual int attack(double characterLuck, bool& loseEquip);
    
    /* Auguments monster's stats by multiplying them by 1.5 */
    void throwFireBall();
};

class Titan : virtual public Monster
{
protected:
    int agility;
public:
    //Constructors
    /* Sets Titan's attributes to starting values */
    Titan(string mName = "", string mDescription = "", double mStrength = 0, double mHealth = 0, double mLuck = 0, bool mAlive = true, double mAgility = 0) : Monster(mName, mDescription, mStrength, mHealth, mLuck, mAlive), agility(mAgility)
    {
        //cout << "Titan ctor" << endl;
        //Set Titan strength
        const int STRENGTH_MIN = 0;
        const int STRENGTH_MAX = 15;
        strength = (rand() % (STRENGTH_MAX - STRENGTH_MIN + 1) + STRENGTH_MIN);
        setStrength(strength);
        
        //Set Titan health
        health = 40;
        setHealth(health);
        
        //Set Titan luck
        const int LUCK_MIN = 0;
        const int LUCK_MAX = 15;
        luck = (rand() % (LUCK_MAX - LUCK_MIN + 1) + LUCK_MIN);
        setLuck(luck);
        
        //Set Titan agility
        const int AGILITY_MIN = 0;
        const int AGILITY_MAX = 20;
        agility = (rand() % (AGILITY_MAX - AGILITY_MIN + 1) + AGILITY_MIN);
        setAgility(agility);
    }
    
    /* Specialized Constructor: Sets Titan's agility to a starting value */
    Titan(double mAgility)
    {
        //cout << "Titan ctor" << endl;
        
        //Set Titan agility
        const int AGILITY_MIN = 0;
        const int AGILITY_MAX = 20;
        agility = (rand() % (AGILITY_MAX - AGILITY_MIN + 1) + AGILITY_MIN);
    }
    
    //Destructor
    virtual ~Titan() {}
    
    //Setters
    /* Sets Titan agility */
    void setAgility(double mAgility)
    {
        agility = mAgility;
    }
    
    //Getters
    /* Returns Titan agility */
    double getAgility() const
    {
        return agility;
    }
    
    //Pure virtual functions
    /* Returns an int representing damage done to the character and causes character to drop one piece of eqipment */
    virtual int attack(double characterLuck, bool& loseEquip);
};

class DragonBoss: public Dragon, public Titan
{
public:
    //Constructor
    /* Initializes DragonBoss's attrubutes to starting values */
    DragonBoss(string mName = "", string mDescription = "", double mStrength = 0, double mHealth = 0, double mLuck = 0, bool mAlive = true, double mVitality = 0, double mAgility = 0) : Monster(mName, mDescription, mStrength, mHealth, mLuck, mAlive), Dragon(mAgility), Titan(mVitality)
    {
        //Set DragonBoss strength
        const int STRENGTH_MIN = 0;
        const int STRENGTH_MAX = 15;
        strength = (rand() % (STRENGTH_MAX - STRENGTH_MIN + 1) + STRENGTH_MIN);
        setStrength(strength);
        
        //Set DragonBoss health
        health = 50;
        setHealth(health);
        
        //Set DragonBoss luck
        const int LUCK_MIN = 0;
        const int LUCK_MAX = 15;
        luck = (rand() % (LUCK_MAX - LUCK_MIN + 1) + LUCK_MIN);
        setLuck(luck);
    }
    
    //Destructor
    virtual ~DragonBoss() {}
    
    /* Returns an int representing damage done to the character */
    virtual int attack(double characterLuck, bool& loseEquip);
};

#endif


