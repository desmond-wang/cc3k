#include <memory>
#include "drow.h"
#include "enemyType.h"
#include "ourUtility.h"
#include "enemy.h"
#include "info.h"
#include "PRNG.h"

using namespace std;

//random number generator declearation
extern PRNG prng1;

Drow::Drow(): maxHP{150}, initAtk{25}, initDef{15}{
    HP = 150;
    Atk = 25;
    Def = 15;
    gold = 0;
}

Drow::~Drow(){};


string Drow::attack(Character &enemy) {
    //use of tool methods from utilities class
    shared_ptr<Utilities> tool = make_shared<Utilities>();
    
    int failsToAttack = prng1(1);
    EnemyType enemyType = dynamic_cast<Enemy&>(enemy).getEnemyType();
    string enemyTypeString = tool->enemyTypeToCharString(enemyType);
    
    // halfling has 50% chance to cause player misses attack
    if (enemyType == EnemyType::halfling){
        if (failsToAttack){
            return "PC's attack misses. ";
        }
    }
    
    // uses double dispatch to deduce enemy's HP
    int damage = enemy.beAttackedBy(*this);
    dynamic_cast<Enemy&>(enemy).setCombatState(false);
    
    // if enemy is merchant, activate its Fight State
    if (enemyType == EnemyType::merchant){
        dynamic_cast<Enemy&>(enemy).setMerchantFightState(true);
    }
    
    // Upon their demise, any enemy that is not a dragon,
    // human, or merchant will drop either a small pile
    // or normal pile of gold. This gold is immediately added
    // to the player character’s total.
    if (enemy.curState().hp <= 0 &&
        enemyType != EnemyType::dragon &&
        enemyType != EnemyType::human &&
        enemyType != EnemyType::merchant)
    {
        int probabilityIndex = prng1(1);
        if (probabilityIndex == 0) gold += 1; //small pile
        if (probabilityIndex == 1) gold += 2; //normal pile
    }
    
    //build and return combatMessage for display
    string combatMessage = "PC deals " + to_string(damage) + " damage to " + enemyTypeString + ". ";
    
    return combatMessage;
}

int Drow::beAttackedBy(Character &enemy) {
    shared_ptr<Enemy> cp = make_shared<Enemy>(dynamic_cast<Enemy&>(enemy));
    
    int damage;
   
    //use of tool methods from utilities class 
    shared_ptr<Utilities> tool = make_shared<Utilities>();
    
    damage =  tool->Damage(Def, enemy.curState().atk);
    looseHP(damage);
    return damage;
 
}

void Drow::consumeGold(class Gold & g) {
    gold += g.getValue();
}

string Drow::consumePotion(shared_ptr<Potion> aPotion) {
    somePotion = aPotion;
    string s = somePotion->usePotion(HP, Atk, Def, 1.5);
    if(HP > maxHP) HP = maxHP;
    if(HP < 0) HP = 0;
    if(Atk < 0) Atk = 0;
    if(Def < 0) Def = 0;
    return s;
}


void Drow::looseHP(int &amount){
    if (HP < amount){
        amount = HP;
        HP = 0;
    } else {
        HP -= amount;
    }
}

Info Drow::curState(){
    return Info{
        HP,Atk,Def
    };
}

void Drow::setToDefaultInfo(){
    Atk = initAtk;
    Def = initDef;
}

playerType Drow::getPlayerType(){
    return playerType::Drow;
}

int Drow::getGold(){
    return gold;
}
