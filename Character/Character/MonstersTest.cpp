/*
 
 AdventureGame
 
 Welcome to the phantasy adventure game! In search for riches and personal glory you have arrived at this
 dark and abandoned dungeon full of dragons and other creatures that lurk from around all corners ready to
 attack you and stall your journey for greatness.
 To find the treasure you will have to navigate through a labyrinth and slay monsters.
 Along the way you will find useful hints that will guide you toward the room with the treasure as well as
 maps that will show you your location in relation to the treasure room. You will collect items that
 will help you recover, kill monsters, and move closer to your goal. You have 3 lives.
 Use them wisely!
 
 */

#include <iostream>
#include <cstdlib>
#include "Dungeon.hpp"
#include "Monster.hpp"
using namespace std;

const int ROWS = 3;
const int COLS = 3;

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));
    bool flag = false;
    
    //TEST CASE #1: Create a Dungeon object
    cout << "TEST CASE #1: Create a Dungeon object" << endl;
    Dungeon dungeon(ROWS, COLS);
    
    //TEST CASE #2: Display Dungeon Rooms (ROOM DEPLOYMENT)
    cout << "\nTEST CASE #2: Display Dungeon Rooms" << endl;
    cout << dungeon;
    
    //TEST CASE #3: Test subscript [][] Operator
    cout << "\nTEST #3: Test subscript [][] Operator" << endl;
    cout << dungeon[0][1];
    cout << dungeon[1][2];
    
    //TEST CASE #4: Test checkNorth function
    cout << "\nTEST #4: Test checkNorth Function" << endl;
    cout << boolalpha << dungeon[0][1].checkNorth() << endl;
    cout << boolalpha << dungeon[0][1].checkEast() << endl;
    
    //TEST CASE #5: Test printMap function
    cout << "\nTEST #5: Test printMap function" << endl;
    dungeon.printMap();
    
    //TEST CASE #6: Test Creating Dragon Objects
    cout << "\nTEST #6: Test Creating Dragon Objects" << endl;
    Dragon dragon1;
    cout << "DRAGON NAME: " << dragon1.getName() << endl;
    cout << "DRAGON DESCRIPTION: " << dragon1.getDescription() << endl;
    cout << "DRAGON STRENGTH: " << dragon1.getStrength() << endl;
    cout << "DRAGON HEALTH: " << dragon1.getHealth() << endl;
    cout << "DRAGON LUCK: "  << dragon1.getLuck() << endl;
    cout << "DRAGON ALIVE: " << boolalpha << dragon1.isAlive() << endl;
    cout << "DRAGON VITALITY: " << dragon1.getVitality() << endl;
    cout << "DAMAGE TO CHARACTER: " << dragon1.attack(8, flag) << endl;
    
    //TEST CASE #7: Test Creating Dragon Objects
    cout << "\nTEST #7: Test Creating Dragon Objects" << endl;
    Dragon dragon2;
    cout << "DRAGON NAME: " << dragon2.getName() << endl;
    cout << "DRAGON DESCRIPTION: " << dragon2.getDescription() << endl;
    cout << "DRAGON STRENGTH: " << dragon2.getStrength() << endl;
    cout << "DRAGON HEALTH: " << dragon2.getHealth() << endl;
    cout << "DRAGON LUCK: "  << dragon2.getLuck() << endl;
    cout << "DRAGON ALIVE: " << dragon2.isAlive() << endl;
    cout << "DRAGON VITALITY: " << dragon2.getVitality() << endl;
    cout << "DAMAGE TO CHARACTER: " << dragon2.attack(8, flag) << endl;
    
    //TEST CASE #8: Test Creating Dragon Objects
    cout << "\nTEST #8: Test Creating Dragon Objects" << endl;
    Dragon dragon3;
    cout << "DRAGON NAME: " << dragon3.getName() << endl;
    cout << "DRAGON DESCRIPTION: " << dragon3.getDescription() << endl;
    cout << "DRAGON STRENGTH: " << dragon3.getStrength() << endl;
    cout << "DRAGON HEALTH: " << dragon3.getHealth() << endl;
    cout << "DRAGON LUCK: "  << dragon3.getLuck() << endl;
    cout << "DRAGON ALIVE: " << dragon3.isAlive() << endl;
    cout << "DRAGON VITALITY: " << dragon3.getVitality() << endl;
    cout << "DAMAGE TO CHARACTER: " << dragon3.attack(8, flag) << endl;
    
    //TEST CASE #9: Test Creating Titan Objects
    cout << "\nTEST #9: Test Creating Titan Objects" << endl;
    Titan titan1;
    cout << "TITAN NAME: " << titan1.getName() << endl;
    cout << "TITAN DESCRIPTION: " << titan1.getDescription() << endl;
    cout << "TITAN STRENGTH: " << titan1.getStrength() << endl;
    cout << "TITAN HEALTH: " << titan1.getHealth() << endl;
    cout << "TITAN LUCK: "  << titan1.getLuck() << endl;
    cout << "TITAN ALIVE: " << titan1.isAlive() << endl;
    cout << "TITAN VITALITY: " << titan1.getAgility() << endl;
    cout << "DAMAGE TO CHARACTER: " << titan1.attack(8, flag) << endl;
    
    //TEST CASE #10: Test Creating Titan Objects
    cout << "\nTEST #10: Test Creating Titan Objects" << endl;
    Titan titan2;
    cout << "TITAN NAME: " << titan2.getName() << endl;
    cout << "TITAN DESCRIPTION: " << titan2.getDescription() << endl;
    cout << "TITAN STRENGTH: " << titan2.getStrength() << endl;
    cout << "TITAN HEALTH: " << titan2.getHealth() << endl;
    cout << "TITAN LUCK: "  << titan2.getLuck() << endl;
    cout << "TITAN ALIVE: " << titan2.isAlive() << endl;
    cout << "TITAN VITALITY: " << titan2.getAgility() << endl;
    cout << "DAMAGE TO CHARACTER: " << titan2.attack(8, flag) << endl;
    
    //TEST CASE #11: Test Creating Titan Objects
    cout << "\nTEST #11: Test Creating Titan Objects" << endl;
    Titan titan3;
    cout << "TITAN NAME: " << titan3.getName() << endl;
    cout << "TITAN DESCRIPTION: " << titan3.getDescription() << endl;
    cout << "TITAN STRENGTH: " << titan3.getStrength() << endl;
    cout << "TITAN HEALTH: " << titan3.getHealth() << endl;
    cout << "TITAN LUCK: "  << titan3.getLuck() << endl;
    cout << "TITAN ALIVE: " << titan3.isAlive() << endl;
    cout << "TITAN VITALITY: " << titan3.getAgility() << endl;
    cout << "DAMAGE TO CHARACTER: " << titan3.attack(8, flag) << endl;
    
    //TEST CASE #12: Test Creating DragonBoss Objects
    cout << "\nTEST #12: Test Creating DragonBoss Objects" << endl;
    DragonBoss dragonBoss1;
    cout << "DRAGONBOSS NAME: " << titan3.getName() << endl;
    cout << "DRAGONBOSS DESCRIPTION: " << titan3.getDescription() << endl;
    cout << "DRAGONBOSS STRENGTH: " << titan3.getStrength() << endl;
    cout << "DRAGONBOSS HEALTH: " << titan3.getHealth() << endl;
    cout << "DRAGONBOSS LUCK: "  << titan3.getLuck() << endl;
    cout << "DRAGONBOSS ALIVE: " << titan3.isAlive() << endl;
    cout << "DRAGONBOSS VITALITY: " << titan3.getAgility() << endl;
    cout << "DAMAGE TO CHARACTER: " << titan3.attack(8, flag) << endl;
    
    //TEST CASE #13: Test Getting Room Description
    cout << "\nTEST #13: Test Getting Room Description" << endl;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            cout << dungeon[i][j].getDescription() << endl;
        }
    }

    return 0;
}


/*
 
 TEST #6: Test Creating Dragon Objects
 DRAGON NAME:
 DRAGON DESCRIPTION:
 DRAGON STRENGTH: 4
 DRAGON HEALTH: 50
 DRAGON LUCK: 11
 DRAGON ALIVE: true
 DRAGON VITALITY: 17
 DAMAGE TO CHARACTER: Watch out! Fire coming your way!
 He hit you! You lost 9 health points.
 9
 
 TEST #7: Test Creating Dragon Objects
 DRAGON NAME:
 DRAGON DESCRIPTION:
 DRAGON STRENGTH: 11
 DRAGON HEALTH: 50
 DRAGON LUCK: 7
 DRAGON ALIVE: true
 DRAGON VITALITY: 18
 DAMAGE TO CHARACTER: Watch out! Fire coming your way!
 He hit you! You lost 24 health points.
 24
 
 TEST #8: Test Creating Dragon Objects
 DRAGON NAME:
 DRAGON DESCRIPTION:
 DRAGON STRENGTH: 10
 DRAGON HEALTH: 50
 DRAGON LUCK: 3
 DRAGON ALIVE: true
 DRAGON VITALITY: 17
 DAMAGE TO CHARACTER: Watch out! Fire coming your way!
 Luckily, he missed this time!
 0
 
 TEST #9: Test Creating Titan Objects
 TITAN NAME:
 TITAN DESCRIPTION:
 TITAN STRENGTH: 14
 TITAN HEALTH: 40
 TITAN LUCK: 1
 TITAN ALIVE: true
 TITAN VITALITY: 16
 DAMAGE TO CHARACTER: You just lost a piece of equimpent. You better pick it back up quickly!
 Luckily, he missed this time!
 0
 
 TEST #10: Test Creating Titan Objects
 TITAN NAME:
 TITAN DESCRIPTION:
 TITAN STRENGTH: 13
 TITAN HEALTH: 40
 TITAN LUCK: 1
 TITAN ALIVE: true
 TITAN VITALITY: 6
 DAMAGE TO CHARACTER: Luckily, he missed this time!
 0
 
 TEST #11: Test Creating Titan Objects
 TITAN NAME:
 TITAN DESCRIPTION:
 TITAN STRENGTH: 11
 TITAN HEALTH: 40
 TITAN LUCK: 5
 TITAN ALIVE: true
 TITAN VITALITY: 16
 DAMAGE TO CHARACTER: You just lost a piece of equimpent. You better pick it back up quickly!
 He hit you! You lost 16 health points.
 16
 
 TEST #12: Test Creating DragonBoss Objects
 DRAGONBOSS NAME:
 DRAGONBOSS DESCRIPTION:
 DRAGONBOSS STRENGTH: 11
 DRAGONBOSS HEALTH: 40
 DRAGONBOSS LUCK: 5
 DRAGONBOSS ALIVE: true
 DRAGONBOSS VITALITY: 16
 DAMAGE TO CHARACTER: You just lost a piece of equimpent. You better pick it back up quickly!
 Luckily, he missed this time!
 0


 */
