#include "ourUtility.h"
#include "enemyType.h"
#include <math.h>
#include <string>

using namespace std;

int Utilities::Damage(int DefenderDef, int AttackerAtk) {
    int result = ceil((100 * AttackerAtk)/(100+DefenderDef));
    return result;
}

string Utilities::enemyTypeToCharString(EnemyType enemyType){
    string toReturn = " ";
    toReturn[0] = static_cast<char>(enemyType);
    return toReturn;
}
