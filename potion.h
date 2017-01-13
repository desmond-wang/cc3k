#ifndef Potion_h
#define Potion_h

#include <string>
#include "item.h"

class Potion : public Item{
protected:
    std::string action;
    
public:
    Potion();
    ~Potion();
    
    virtual std::string usePotion(int &hp, int &atk, int &def, double multiple = 1) = 0;
    int getValue() override { return -1; }
};

//Restore health (RH): restore up to 10 HP
class PotionRH : public Potion {
public:
    PotionRH();
    ~PotionRH() {}
    std::string usePotion(int &hp, int &atk, int &def, double multiple = 1) override;
};

//Boost Atk (BA): increase ATK by 5
class PotionBA : public Potion {
public:
    PotionBA();
    ~PotionBA() {}
    std::string usePotion(int &hp, int &atk, int &def, double multiple = 1) override;
};

//Boost Def (BD): increase Def by 5
class PotionBD : public Potion {
public:
    PotionBD();
    ~PotionBD() {}
    std::string usePotion(int &hp, int &atk, int &def, double multiple = 1) override;
};

//Poison health (PH): lose up to 10 HP
class PotionPH : public Potion {
public:
    PotionPH();
    ~PotionPH() {}
    std::string usePotion(int &hp, int &atk, int &def, double multiple = 1) override;
};

//Wound Atk (WA): decrease Atk by 5
class PotionWA : public Potion {
public:
    PotionWA();
    ~PotionWA() {}
    std::string usePotion(int &hp, int &atk, int &def, double multiple = 1) override;
};

//Wound Def (WD): decrease Def by 5
class PotionWD : public Potion {
public:
    PotionWD();
    ~PotionWD() {}
    std::string usePotion(int &hp, int &atk, int &def, double multiple = 1) override;
};


#endif
