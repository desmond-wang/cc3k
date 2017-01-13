#ifndef Enemy_h
#define Enemy_h

#include <string>
#include <memory>
#include "character.h"
#include "player.h"
#include "enemyType.h"
#include "info.h"
#include "gold.h"

class Enemy: public Character {
    EnemyType enemyType;
    
    //determines whether an enemy's reaction to players action
    //is to fight back (combatState = true) or is to move
    //(combatState = false)
    bool combatState;
    
    //specifically for EnemyType::Merchant, to determine if it is in "can
    //-fight" state as other enemies.
    static bool merchantFightState;
    
    //specifically for EnemyType::Dragon. sets gold to consumable when
    //Dragon dies.
    std::shared_ptr<Gold> gold;
    
public:
    //constructor based on input enemyType
    Enemy(EnemyType type, std::shared_ptr<Gold> gold = nullptr);
    
    //destructor
    ~Enemy();
    
    //set merchantFightState to state
    static void setMerchantFightState(bool state);
    
    //get merchantFightState
    static bool getMerchantFightState();
    
    //attack the input player character and return a combat
    //message string
    std::string attack (Character &player) override;
    
    //deduct HP and return the amount of HP being deducted
    int beAttackedBy (Character &player) override;
    
    //get the race of this enemy (eg. Human)
    EnemyType getEnemyType();
    
    //get combatState
    bool getCombatState();
    
    //set combatState to state;
    void setCombatState(bool state);
    
    //get the current HP, Atk, Def information of this enemy
    virtual Info curState()override;
    
    //set gold to consumable
    void releaseGold();

private:
    //reduce input amount of HP. if HP is lower than input amount,
    //set amount to HP and reduce HP to 0.
    void looseHP(int &amount)override;
};

#endif
