#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <memory>
#include "character.h"
#include "gold.h"
#include "potion.h"
#include "playerType.h"
#include "info.h"

class Player: public Character{ //has subclass Drow, Goblin, Shade, Troll, Vampire
protected:
    int gold;
    std::shared_ptr<Potion>somePotion;
    
public:
    // get the race of this player (eg. Shade)
    virtual playerType getPlayerType() = 0;

    // get the amount of gold this player has
    virtual int getGold() = 0;

    // set the player's Atk and Def to initial value
    virtual void setToDefaultInfo() = 0;

    // increase the player's amount of gold
    virtual void consumeGold(Gold &g) = 0;

    // increase or decrease player's HP, Def, Atk based on potion's type
    virtual std::string consumePotion(std::shared_ptr<Potion> potion) = 0;
};

#endif
