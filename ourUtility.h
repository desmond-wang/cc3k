#ifndef Utility_h
#define Utility_h

#include <string>
#include "enemyType.h"

class Utilities {
public:
    int Damage (int DefenderDef, int AttackerAtk);
    std::string enemyTypeToCharString (EnemyType enemyType);
};

#endif 
