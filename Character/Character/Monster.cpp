/*
 
 Implementation file for the Monster class.
 
 */

#include "Monster.h"

/********************************************************************************************
 setHealth
 Sets monster health.
 *******************************************************************************************/
void Monster::setHealth(double mHealth)
{
    health = mHealth;
    if (health <= 0)
    {
        alive = false;
    }
}

/********************************************************************************************
 setStrength
 Sets monster strength.
 *******************************************************************************************/
void Monster::setStrength(double mStrength)
{
    strength = mStrength;
}

/********************************************************************************************
 setLuck
 Sets monster luck.
 *******************************************************************************************/
void Monster::setLuck(double mLuck)
{
    luck = mLuck;
}

/********************************************************************************************
 setAlive
 Sets monster alive status.
 *******************************************************************************************/
void Monster::setAlive(bool mAlive)
{
    alive = mAlive;
}

/********************************************************************************************
 modifyHealth
 Modifies monster's health by subtracting the amount of damage.
 Returns true if the monster is still alive and false if he is dead.
 *******************************************************************************************/
bool Monster::modifyHealth(double mDamage)
{
    health -= mDamage;
    if (health <= 0)
    {
        alive = false;
        cout << name << " burnt in flames and died." << endl;
    }
    return alive;
}

/********************************************************************************************
 getName
 Returns monster name.
 *******************************************************************************************/
string Monster::getName() const
{
    return name;
}
/********************************************************************************************
 getDescription
 Returns monster description
 *******************************************************************************************/
string Monster::getDescription() const
{
    return description;
}

/********************************************************************************************
 getStrength
 Returns monster strength
 *******************************************************************************************/
double Monster::getStrength() const
{
    return strength;
}

/********************************************************************************************
 getHealth
 Returns monster health
 *******************************************************************************************/
double Monster::getHealth() const
{
    return health;
}

/********************************************************************************************
 getLuck
 Returns monster luck
 *******************************************************************************************/
double Monster::getLuck() const
{
    return luck;
}

/********************************************************************************************
 isAlive
 Returns if a monster is dead or alive
 *******************************************************************************************/
bool Monster::isAlive() const
{
    return alive;
}

/********************************************************************************************
 Dragon's Constructor
 Initializes dragon attributes to starting values
 *******************************************************************************************/
Dragon::Dragon(string mName, string mDescription, double mStrength, double mHealth, double mLuck, bool mAlive, double mVitality) : Monster(mName, mDescription, mStrength, mHealth,  mLuck, mAlive), vitality(mVitality)
{
    //Set Dragon strength
    const int STRENGTH_MIN = 3;
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

/********************************************************************************************
 Dragon's Specialized Constructor
 Initializes Dragon's vitality - data not inherited from the Monster class.
 *******************************************************************************************/
Dragon::Dragon(double mVitality)
{
    //Set Dragon vitality
    const int VITALITY_MIN = 0;
    const int VITALITY_MAX = 20;
    vitality = (rand() % (VITALITY_MAX - VITALITY_MIN + 1) + VITALITY_MIN);
    setVitality(vitality);
}

/********************************************************************************************
 setVitality
 Sets Dragon vitality
 *******************************************************************************************/
void Dragon::setVitality(double mVitality)
{
    vitality = mVitality;
}

/********************************************************************************************
 getVitality
 Returns Dragon vitality
 *******************************************************************************************/
double Dragon::getVitality() const
{
    return vitality;
}

/********************************************************************************************
 Titan's Constructor
 Sets Titan's attributes to starting values 
 *******************************************************************************************/
Titan::Titan(string mName, string mDescription, double mStrength, double mHealth, double mLuck, bool mAlive, double mAgility) : Monster(mName, mDescription, mStrength, mHealth, mLuck, mAlive), agility(mAgility)
{
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

/********************************************************************************************
 Titan's Specialized Constructor
 Sets Titan's agility to a starting value
 *******************************************************************************************/
Titan::Titan(double mAgility)
{
    
    //Set Titan agility
    const int AGILITY_MIN = 0;
    const int AGILITY_MAX = 20;
    agility = (rand() % (AGILITY_MAX - AGILITY_MIN + 1) + AGILITY_MIN);
}

/********************************************************************************************
 setAgility
 Sets Titan agility.
 *******************************************************************************************/
void Titan::setAgility(double mAgility)
{
    agility = mAgility;
}

/********************************************************************************************
 getAgility
 Returns Titan's agility.
 *******************************************************************************************/
double Titan::getAgility() const
{
    return agility;
}

/********************************************************************************************
 DragonBoss's Constructor
 Initializes DragonBoss's attrubutes to starting values
 *******************************************************************************************/
DragonBoss::DragonBoss(string mName, string mDescription, double mStrength, double mHealth, double mLuck, bool mAlive, double mVitality, double mAgility) : Monster(mName, mDescription, mStrength, mHealth, mLuck, mAlive), Dragon(mAgility), Titan(mVitality)
{
    //Set DragonBoss strength
    const int STRENGTH_MIN = 15;        
    const int STRENGTH_MAX = 30;
    strength = (rand() % (STRENGTH_MAX - STRENGTH_MIN + 1) + STRENGTH_MIN);
    setStrength(strength);
    
    //Set DragonBoss health
    health = 200;
    setHealth(health);
    
    //Set DragonBoss luck
    const int LUCK_MIN = 0;
    const int LUCK_MAX = 15;
    luck = (rand() % (LUCK_MAX - LUCK_MIN + 1) + LUCK_MIN);
    setLuck(luck);
}


/********************************************************************************************
 getHitAccuracy
 Computes the strength of a monster hit by assigning it a random int from range 1-100.
 Computes the strength of a character hit by assigning it a random int from range 1-100.
 Multiplies each number by monster's and character's luck expressed as a percentage.
 Returns true (monster hit was successful) if the strength of monster's attack was higher
 than the strength of character's attack.
 *******************************************************************************************/
bool Monster::getHitAccuracy(double characterLuck) const
{
    //Generate an int from range 1-100 representing the strength of monster's attack
    double monsterHit = rand() % 100 + 1;
    
    //Generate an int from range 1-100 representing the strength of character's attack
    double characterHit = rand() % 100 + 1;
    
    //Multiply both hits by monster's and character's luck expressed as a percentage
    monsterHit *= (1 + (luck / 100.0));
    characterHit *= (1 + (characterLuck / 100.0));
    
    return (monsterHit >= characterHit);
}

/********************************************************************************************
 throwFireBall
 Auguments monster stats by multipling strength and luck by 1.25.
 *******************************************************************************************/
void Dragon::throwFireBall()
{
    const double MULTIPLIER = 1.25;
    setStrength(strength * MULTIPLIER);
    setLuck(luck * MULTIPLIER);
}

/********************************************************************************************
 attack
 Throws a fireball if dragon's vitality is > 12. Computes and returns damage done to the
 character by multiplying the character's strength by 1.5.
 *******************************************************************************************/
int Dragon::attack(double characterLuck)
{
     int damage = 0;
    
    //If monster's attack was accurate, compute damage
    if (getHitAccuracy(characterLuck))
    {
        damage = strength * 1.5;
        
        //If dragons's vitality is > 12, throw a fireball
        if (vitality > 12)
        {
            throwFireBall();
            cout << "Watch out! Fire coming your way!" << endl;
        }
        cout << "He hit you! You lost " << damage << " health points." << endl;
    }
    else
    {
        cout << "Luckily, he missed this time!" << endl;
    }
    
    return damage;
}

/********************************************************************************************
 attack
 If titan's agility is > 12, critical hit is dealt.
 Computes and returns damage done to the character by multiplying the character's strength by 1.5.
 *******************************************************************************************/
int Titan::attack(double characterLuck)
{
    int damage = 0;
    
    //If monster's attack was accurate, compute damage
    if (getHitAccuracy(characterLuck))
    {
        damage = strength * 1.65;
        
        //If titan's agility is > 12 deal a critical hit
        if (agility > 12)
        {
            double modifier = (rand()% 10 + 1) / 10.0 + 1;
            damage *= modifier;
            cout << "He dealt you a critical hit! " << endl;
        }
        cout << "He hit you! You lost " << damage << " health points." << endl;
    }
    else
    {
        cout << "Luckily, he missed this time!" << endl;
    }
    return damage;
}

/********************************************************************************************
 attack
 Throws a fireball if dragonboss's vitality is > 12. Causes character to drop equipment if
 dragonboss's agility is > 12.  Computes and returns damage done to the character by multiplying
 the character's strength by 1.5.
 *******************************************************************************************/
int DragonBoss::attack(double characterLuck)
{
    int damage = 0;
    
    //If monster's attack was accurate, compute damage
    if (getHitAccuracy(characterLuck) && vitality > 12)
    {
        damage = strength * 1.5;
        
        //If dragonboss's vitality is > 12, throw a fireball
        if (vitality > 12)
        {
            throwFireBall();
            cout << "Watch out! Fire coming your way!" << endl;
        }
    
        //If dragonboss's agility is > 12, deal a critical hit
        if (agility > 12)
        {
            double modifier = (rand()% 10 + 1) / 10.0 + 1;
            damage *= modifier;
            cout << "He also dealt you a critical hit! " << endl;
        }
        cout << "He hit you! You lost " << damage << " health points." << endl;
    }
    else
    {
        cout << "Luckily, he missed this time!" << endl;
    }
    
    return damage;
}



