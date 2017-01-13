#include <memory>
#include <iostream>
#include <string>
#include "enemy.h"
#include "enemyType.h"
#include "direction.h"
#include "info.h"
#include "player.h"
#include "ourUtility.h"
#include "PRNG.h"

using namespace std;

//random number generator declearation
extern PRNG prng1;

//merchant is defaulted to be neutral, which does not actively fight
bool Enemy::merchantFightState = false;

//constructor for different type of enemies with different HP,Atk,Def
Enemy::Enemy(EnemyType type, shared_ptr<Gold> gold):
enemyType{type}, gold{gold}{
    if (enemyType == EnemyType::human)
    {
        HP = 140;
        Atk = 20;
        Def = 20;
    } else if (enemyType == EnemyType::dwarf) {
        HP = 100;
        Atk = 20;
        Def = 30;
    } else if (enemyType == EnemyType::elf) {
        HP = 140;
        Atk = 30;
        Def = 10;
    } else if (enemyType == EnemyType::orc) {
        HP = 180;
        Atk = 30;
        Def = 25;
    } else if (enemyType == EnemyType::merchant) {
        HP = 30;
        Atk = 70;
        Def = 50;
    } else if (enemyType == EnemyType::dragon) {
        HP = 150;
        Atk = 20;
        Def = 20;
    } else { //if (enemyType == EnemyType::halfling)
        HP = 100;
        Atk = 15;
        Def = 20;
    }
    combatState = false;
    
}

Enemy::~Enemy() {}

string Enemy::attack (Character &player) {
    //use of tool methods from utilities class
    shared_ptr<Utilities> tool = make_shared<Utilities>();
    
    // sotre enemyType as a string
    string enemyTypeString = tool->enemyTypeToCharString(enemyType);
    
    
    // Enemy has 50% to miss to attack
    int failsToAttack = prng1(1);
    if (failsToAttack) {
        combatState = false;
        return enemyTypeString + "'s attack misses. ";
    }
    
    // uses double dispatch to deduce player's HP
    int damage;
    if (enemyType == EnemyType::elf){
        // Elf takes two attacks
        damage = dynamic_cast<Player&>(player).beAttackedBy(*this);
        damage += dynamic_cast<Player&>(player).beAttackedBy(*this);
    } else {
        // regular damage for other eneyTypes
        damage = dynamic_cast<Player&>(player).beAttackedBy(*this);
    }
    
    // reset combatState to false, so enemies don't keep attacking
    // the player when player is out of the 8-block range.
    combatState = false;

    
    //build and return combatMessage for display
    string combatMessage = enemyTypeString + " deals " +
        to_string(damage) + " damage to PC. ";
    return combatMessage;
}

int Enemy::beAttackedBy (Character &player) {
    //use of tool methods from utilities class
    shared_ptr<Utilities> tool = make_shared<Utilities>();
    
    Player& pr = dynamic_cast<Player&>(player);
    int damage;

    damage =  tool->Damage(Def, pr.curState().atk);
    
    looseHP(damage);
    return damage;
}


EnemyType Enemy::getEnemyType(){
    return enemyType;
}

bool Enemy::getCombatState(){
    return combatState;
}

void Enemy::setCombatState(bool state){
    combatState = state;
}


Info Enemy::curState(){
    return Info{
        HP,Atk,Def
    };
}


void Enemy::looseHP(int &amount){
    if (HP < amount){
        amount = HP;
        HP = 0;
    } else {
        HP -= amount;
    }
}


bool Enemy::getMerchantFightState(){
    return merchantFightState;
}

void Enemy::setMerchantFightState(bool state){
    merchantFightState = state;
}

void Enemy::releaseGold(){
    gold->release();
}
