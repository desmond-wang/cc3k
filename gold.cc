#include <memory>
#include "gold.h"
#include "enemy.h"
#include "enemyType.h"

using namespace std;
Gold::Gold(GoldType g):type{g}{
    value = static_cast<int>(g);
    if (type == GoldType::dragonHoard)
    {
        consumable = false;
    } else {
        consumable = true;
    }
}

Gold::~Gold(){};

int Gold::getValue(){
    return value;
}

GoldType Gold:: getType(){
    return type;
}

void Gold::release(){
    consumable = true;
}

bool Gold::isConsumable(){
    return consumable;
};

