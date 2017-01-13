#ifndef Troll_h
#define Troll_h

#include <string>
#include "player.h"


class Troll : public Player {
    int maxHP;
    int initAtk;
    int initDef;
    
public:
    Troll();
    ~Troll();
   
    // get the amount of gold this player has 
    int getGold() override;

    // returns an Info structure with current HP, Atk, Def
    Info curState()override;

    // returns an Info structure with current HP, Atk, Def
    void setToDefaultInfo() override;

    // returns playerType::Drow
    playerType getPlayerType()override;

    // attack the input player character and return a combat
    // message string
    std::string attack(Character &enemy) override;

    // deduct HP and return the amount of HP being deducted
    int beAttackedBy(Character &enemy)override;

    // increase the player's amount of gold
    void consumeGold(Gold & g) override ;

    // increase or decrease player's HP, Def, Atk based on potion's type
    std::string consumePotion(std::shared_ptr<Potion>) override;

    // add 5HP to the player and make sure HP does not exceeds maxHP
    void addHP();

private :
    //reduce input amount of HP. if HP is lower than input amount,
    //set amount to HP and reduce HP to 0.
    void looseHP(int &amount) override;
};

#endif
