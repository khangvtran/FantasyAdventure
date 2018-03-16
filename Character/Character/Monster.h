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
 If dragon's vitality is > 12, the attack function will also include throwing fireballs, which
 augument monster's strength and luck by 1.5.
 Titan contains an additional data member of agility which is a random number from range 0-20.
 If titan's agility is > 12, the attack function will also include dealing a critical hit to the character.
 The DragonBoss class derives from both the Dragon and Titan. It contains its own attack method that
 makes it throw fireballs if its vitality is > 12 and deal a critical hit to the character if its agility is > 12.
 
 */

#ifndef Monster_h
#define Monster_h

#include <iostream>
#include <string>

class Monster
{
protected:
    std::string name;                    //stores monster name
    std::string description;             //stores monster description
    double strength;                     //stores monster's strength
    double health;                       //stores monster's health
    double luck;                         //stores monster's luck
    double alive;                        //flag to indicate whether a monster is dead or alive
public:
    //Constructor
    /* Initializes monster data with starting values */
    Monster(const std::string& mName = "", const std::string& mDescription = "", double mStrength = 0, double mHealth = 0, double mLuck = 0, bool mAlive = true) : name(mName), description(mDescription), strength(mStrength), health(mHealth), luck(mLuck), alive(mAlive) {}
    
    //Destructor
    virtual ~Monster() {}
    
    //Setters
    /* Sets monster health */
    void setHealth(double mHealth);
    
    /* Sets monster strength */
    void setStrength(double mStrength);
    
    /* Sets monster luck */
    void setLuck(double mLuck);
    
    /* Sets monster alive status */
    void setAlive(bool mAlive);
    
    /* Modifies monster's health by subtracting the amount of damage. Returns true if the monster is still alive and false if he is dead. */
    bool modifyHealth(double mDamage);
    
    //Getters
    /* Returns monster name */
    std::string getName() const;
    
    /* Returns monster description */
    std::string getDescription() const;
    
    /* Returns monster strength */
    double getStrength() const;
    
    /* Returns monster health */
    double getHealth() const;
    
    /* Returns monster luck */
    double getLuck() const;
    
    /* Returns if a monster is dead or alive */
    bool isAlive() const;
    
    /* Returns true if monster attack was a hit and false if it was a miss */
    bool getHitAccuracy(double characterLuck) const;
    
    //Pure virtual functions
    /* Returns an int representing damage done to the character */
    virtual int attack(double characterLuck) = 0;
    
};

class Dragon : virtual public Monster
{
protected:
    double vitality;
public:
    //Constructors
    /* Initializes dragon attributes to starting values */
    Dragon(const std::string& mName = "", const std::string& mDescription = "", double mStrength = 0, double mHealth = 0, double mLuck = 0, bool mAlive = true, double mVitality = 0);
    
    /* Specialized constructor: Initializes Dragon's vitality - data not inherited from the Monster class */
    Dragon(double mVitality);
    
    //Destructor
    virtual ~Dragon() {}
    
    //Setters
    /* Sets Dragon vitality */
    void setVitality(double mVitality);
    
    //Getters
    /* Returns Dragon vitality */
    double getVitality() const;
    
    //Pure virtual functions
    /* Returns an int representing damage done to the character */
    virtual int attack(double characterLuck) override;
    
    /* Auguments monster's stats by multiplying strength and luck by 1.25 */
    void throwFireBall();
};

class Titan : virtual public Monster
{
protected:
    int agility;
public:
    //Constructors
    /* Sets Titan's attributes to starting values */
    Titan(const std::string& mName = "", const std::string& mDescription = "", double mStrength = 0, double mHealth = 0, double mLuck = 0, bool mAlive = true, double mAgility = 0);
    
    /* Specialized Constructor: Sets Titan's agility to a starting value */
    Titan(double mAgility);
    
    //Destructor
    virtual ~Titan() {}
    
    //Setters
    /* Sets Titan agility */
    void setAgility(double mAgility);
    
    //Getters
    /* Returns Titan agility */
    double getAgility() const;
    
    //Pure virtual functions
    /* Returns an int representing damage done to the character and causes character to drop one piece of eqipment */
    virtual int attack(double characterLuck) override;
};

class DragonBoss: public Dragon, public Titan
{
public:
    //Constructor
    /* Initializes DragonBoss's attrubutes to starting values */
    DragonBoss(const std::string& mName = "", const std::string& mDescription = "", double mStrength = 0, double mHealth = 0, double mLuck = 0, bool mAlive = true, double mVitality = 0, double mAgility = 0);
    
    //Destructor
    virtual ~DragonBoss() {}
    
    /* Returns an int representing damage done to the character */
    virtual int attack(double characterLuck) override;
};

#endif


