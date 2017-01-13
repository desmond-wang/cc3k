#include "potion.h"
using namespace std;

Potion::Potion(){}

Potion::~Potion(){}

//RH
PotionRH::PotionRH() {
    value = 10;
    action = "PC uses RH. ";
}

string PotionRH::usePotion(int &hp, int &atk, int &def, double m){
    hp += value*m;
    return action;
}

//BA
PotionBA::PotionBA() {
    value = 5;
    action = "PC uses BA. ";
}

string PotionBA::usePotion(int &hp, int &atk, int &def, double m){
    atk += value*m;
    return action;
}

//BD
PotionBD::PotionBD() {
    value = 5;
    action = "PC uses BD. ";
}

string PotionBD::usePotion(int &hp, int &atk, int &def, double m){
    def += value*m;
    return action;
}

//PH
PotionPH::PotionPH() {
    value = 10;
    action = "PC uses PH. ";
}
  
string PotionPH::usePotion(int &hp, int &atk, int &def, double m){
    hp -= value*m;
    return action;
}

//WA
PotionWA::PotionWA() {
    value = 5;
    action = "PC uses WA. ";
}
 
string PotionWA::usePotion(int &hp, int &atk, int &def, double m){
    atk -= value*m;
    return action;
}

//WD
PotionWD::PotionWD() {
    value = 5;
    action = "PC uses WD. ";
}

string PotionWD::usePotion(int &hp, int &atk, int &def, double m){
    def -= value*m;
    return action;
}

