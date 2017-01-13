#include <memory>
#include <iostream>
#include "shade.h"
#include "enemyType.h"
#include "ourUtility.h"
#include "enemy.h"
#include "info.h"
#include "PRNG.h"

using namespace std;

//random number generator declearation
extern PRNG prng1;

Shade::Shade(): maxHP{125}, initAtk{25}, initDef{25}{
    HP = 125;
    Atk = 25;
    Def = 25;
    gold = 0;
}

Shade::~Shade(){}


string Shade::attack(Character &enemy) {
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



int Shade::beAttackedBy(Character &enemy) {
    //use of tool methods from utilities class
    shared_ptr<Utilities> tool = make_shared<Utilities>();
    
    shared_ptr<Enemy> cp = make_shared<Enemy>(dynamic_cast<Enemy&>(enemy));
    int damage =  tool->Damage(Def, enemy.curState().atk);
    looseHP(damage);
    return damage;
}

void Shade::consumeGold(class Gold & g) {
    gold += g.getValue();
}

string Shade::consumePotion(shared_ptr<Potion> aPotion) {
    somePotion = aPotion;
    string s = somePotion->usePotion(HP, Atk, Def);
    if(HP > maxHP) HP = maxHP;
    if(HP < 0) HP = 0;
    if(Atk < 0) Atk = 0;
    if(Def < 0) Def = 0;
    return s;
}

void Shade::looseHP(int &amount){
    if (HP < amount){
        amount = HP;
        HP = 0;
        // this need to be destroyed
    } else {
        HP -= amount;
    }
}

Info Shade::curState(){
    return Info{
        HP, Atk, Def
    };
}

void Shade::setToDefaultInfo(){
    Atk = initAtk;
    Def = initDef;
}

playerType Shade::getPlayerType(){
    return playerType::Shade;
}

int Shade::getGold(){
    return gold;
}

