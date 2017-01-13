#ifndef Character_h
#define Character_h

#include <string>
#include "info.h"

class Character { //has subclass Player and Enemy
protected:
    int HP;
    int Atk;
    int Def;
    
public:
    //attack the input player character and return a combat
    //message string
    virtual std::string attack(Character &c) = 0;

    //deduct HP and return the amount of HP being deducted
    virtual int beAttackedBy(Character &c) = 0;

    //get the current HP, Atk, Def information of this character
    virtual Info curState() = 0;
    
private:
    //reduce input amount of HP. if HP is lower than input amount,
    //set amount to HP and reduce HP to 0.
    virtual void looseHP(int &amount) = 0;
};

#endif
