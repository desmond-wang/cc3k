#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <memory>
#include "PRNG.h"
#include "floor.h"
#include "cell.h"
#include "character.h"
#include "player.h"
#include "enemy.h"
#include "posn.h"
#include "drow.h"
#include "shade.h"
#include "troll.h"
#include "vampire.h"
#include "goblin.h"
#include "item.h"
#include "gold.h"
#include "goldType.h"
#include "potion.h"

struct ChamberAndPosn {
    int chamber;
    Posn pos;
};

class Game{
    /* #################### privite field ############################ */
    // Store playerRace for cout use.
    std::string playerRace;
    
    // Store fllor number to know which floor is hero current on
    int floorNum = 1;
    
    // Store floor to cout the map.
    Floor fl;
    
    // Provent delete player when go to next floor
    std::shared_ptr<Player> player;
    
    // Using bool to determine enemy move or not
    bool isEnemyMove = true;
    
    // Check using which map(empty map or map with npc and pc alreaday given on map) we use.
    bool isDefaultMap;
    
    // Store file number for next floor use.
    std::string fileName;
    
    /* #################### privite method ############################ */
    
    // Generate a random poson in ramdom cell, and return a struct called
    // ChamberAndPosn, which is the chamber number of this positon for futher
    // use and the corrodinate of cell.
    ChamberAndPosn initRandom();
    
    // Check the cell oppupied or not from initRadom() if not, then genrate the cell in that
    // coordinate, return the cellPtr
    std::shared_ptr<Cell> availableTile();
    
    // To initial certain player type from user input selection.
    void initPlayerPtr();
    
    // To set player into cell and intial stair depend on player chamber so that staire cannot
    // generate in the same chamber with player.
    void setPlayerAndStair();
    
    // Random generate enemy by flowing the desired probability.
    char randomNpc();
    
    // Initial the enemy(non player character) and set the symbol and pointer into cell, then
    // put back to floor.
    void initNpc ();
    
    // Random initial the potion by using PRNG to slelect the potion type, and set symbol nad pointer
    // in cell, then put back to floor.
    void initPotion();
    
    // Random initial the gold by using PRNG to slelect the gold type, and set symbol nad pointer
    // in cell, then put back to floor.
    void initGold();
    
    // Initial dragon by create DragonPtr  whcih is making a enemy pointer (dragon, and given
    // dragon gold pointer under enemy field), and create a cell pointer of dragon, and put
    // back in floor.
    void initDragon (std::shared_ptr<Cell>, std::shared_ptr<Gold>);
    
    // attack() read an user input direction then call floor attckNeighbour method.
    void attack();
    
    // change user input dirction to integer number for floor to use.
    int moveIndex(std::string);
    
    // eatPotion() read an user input direction then call floor consumePotion method.
    void eatPotion();
    
    // print the hero, gold, floor level, and action.
    void printStatus(std::string);
    
    // Cout message and check the user input is quit or restart.
    bool isQuit(std::string);
    
    // check if the map is defalut of not to detemine which function to call when restart.
    void restartMap();
    
    // print cover txt
    void printCover(std::string);


public:
    /* #################### public method ############################ */
    ~Game();
    Game();
    // read map with eveything already initialed.
    void Init(std::string filename);
    // read empty map and intial all the character and item.
    void defaultInit();
    // start to move attack and use potion(game start).
    void start();
};
#endif
