#ifndef Gold_h
#define Gold_h

#include <memory>
#include "item.h"
#include "goldType.h"

class Enemy;

class Gold: public Item{
    GoldType type;
    bool consumable;
    
public:
    Gold(GoldType type);
    ~Gold();

    // get the value of the gold
    int getValue() override;

    // get the type of the gold (eg. dragonHoard)
    GoldType getType();

    // set consumable to true
    void release();

    // get consumable
    bool isConsumable();
};


#endif
