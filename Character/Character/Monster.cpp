/*
 
 Implementation file for the Monster class.
 
 */

#include "Monster.h"

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
    //cout << "MONSTER HIT: " << monsterHit << endl;
    
    //Generate an int from range 1-100 representing the strength of character's attack
    double characterHit = rand() % 100 + 1;
    //cout << "CHARACTER HIT: " << characterHit << endl;
    
    //Multiply both hits by monster's and character's luck expressed as a percentage
    monsterHit *= (1 + (luck / 100.0));
    characterHit *= (1 + (characterLuck / 100.0));
    //cout << "ADJUSTED MONSTER HIT: " << monsterHit << endl;
    //cout << "ADJUSTED CHARACTER HIT: " << characterHit << endl;
    
    return (monsterHit >= characterHit);
}

/********************************************************************************************
 throwFireBall
 Auguments monster stats by multipling strength and luck by 1.5.
 *******************************************************************************************/
void Dragon::throwFireBall()
{
    const double MULTIPLIER = 1.5;
    setStrength(strength * MULTIPLIER);
    //cout << "STRENGTH * 1.5: " << strength << endl;
    setLuck(luck * MULTIPLIER);
    //cout << "LUCK * 1.5: " << luck << endl;
}

/********************************************************************************************
 attack
 Throws a fireball if dragon's vitality is > 10. Computes and returns damage done to the
 character by multiplying the character's strength by 1.5.
 *******************************************************************************************/
int Dragon::attack(double characterLuck, bool& loseEquip)
{
    int damage = 0;
    
    //If dragons's vitality is > 10, throw a fireball
    //cout << "THROW FIRE BALL: " << (vitality > 10) << endl;
    if (vitality > 10)
    {
        cout << "Watch out! Fire coming your way!" << endl;
        throwFireBall();
    }
    
    //If monster's attack was accurate, compute damage
    if (getHitAccuracy(characterLuck))
    {
        damage = strength * 1.5;
        cout << "He hit you! You lost " << damage << " health points." << endl;
        //cout << "DAMAGE: " << damage << endl;
    }
    else
    {
        cout << "Luckily, he missed this time!" << endl;
    }
    
    return damage;
}

/********************************************************************************************
 attack
 If titan's agility is > 10, the character's equipment is knocked down.
 Computes and returns damage done to the character by multiplying the character's strength by 1.5.
 *******************************************************************************************/
int Titan::attack(double characterLuck, bool& loseEquip)
{
    int damage = 0;
    
    //If titan's agility is > 10, set loseEquipment flag to true
    if (agility > 10)
    {
        cout << "You just lost a piece of equimpent. You better pick it back up quickly!" << endl;
        loseEquip = true;
    }
    
    
    //If monster's attack was accurate, compute damage
    if (getHitAccuracy(characterLuck))
    {
        damage = strength * 1.5;
        cout << "He hit you! You lost " << damage << " health points." << endl;
        //cout << "DAMAGE: " << damage << endl;
    }
    else
    {
        cout << "Luckily, he missed this time!" << endl;
    }
    return damage;
}

/********************************************************************************************
 attack
 Throws a fireball if dragonboss's vitality is > 10. Causes character to drop equipment if
 dragonboss's agility is > 10.  Computes and returns damage done to the character by multiplying
 the character's strength by 1.5.
 *******************************************************************************************/
int DragonBoss::attack(double characterLuck, bool& loseEquip)
{
    int damage = 0;
    
    //If dragonboss's vitality is > 10, throw a fireball
    if (vitality > 10)
    {
        cout << "Watch out! Fire coming your way!" << endl;
        throwFireBall();
    }
    
    //If dragonboss's agility is > 10, set loseEquipment flag to true
    if (agility > 10)
    {
        cout << "You just lost a piece of equimpent. You better pick it back up quickly!" << endl;
        loseEquip = true;
    }
    
    //If monster's attack was accurate, compute damage
    if (getHitAccuracy(characterLuck))
    {
        damage = strength * 1.5;
        cout << "He hit you! You lost " << damage << " health points." << endl;
        //cout << "DAMAGE: " << damage << endl;
    }
    else
    {
        cout << "Luckily, he missed this time!" << endl;
    }
    
    return damage;
}



