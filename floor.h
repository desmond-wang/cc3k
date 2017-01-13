#ifndef __FLOOR_H__
#define __FLOOR_H__
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "cell.h"
#include "posn.h"
#include "PRNG.h"
#include "player.h"
#include "gold.h"
#include "textdisplay.h"

class Floor {
    // The actual floor of Cell pointer
    std::vector<std::vector<std::shared_ptr<Cell>>> theFloor;  
    // Save positions of tiles in each chamber
    std::vector<std::vector<Posn>> chamberTiles;
    // Save a char map for move Enemies
    std::vector<std::vector<char>> enemyMoveMap;
    // TextDisplay
    std::shared_ptr<TextDisplay> td;
    // Positon of the Player
    Posn heroPosn;
    // String infomation after player moves , attacks, or uses potion
    std::string errorMsg;
    // Store string infomation for action
    std::string action;

    char curSymbol = '.'; 
    char nextSymbol = '.';
    // For set back + # G


    // Tranlate direction from int to string
    std::string moveDirction(int); 
    // Bool for whether showing potion number info, moveHero true, otherwise false
    void notifyNeighbours(std::shared_ptr<Cell>, bool);
    // Add 8 neighbour cells to current cell
    void addNeighbours();

public:
    Floor();
    ~Floor();

    // init the default empty map
    void initDefault();
    // Sets up the floor from name (the given map)
    void init(std::string name, std::shared_ptr<Player>, int);

    // Set Player position
    void setHeroPosn(Posn);

    // Returns 5 chambers and their empty tiles to Game for random generation
    std::vector<std::vector<Posn>> getChamberTiles();
    // return the cell of the required posn
    std::shared_ptr<Cell> getCell(Posn);
    
    // Moves enemies
    void moveEnemies();
    // Move Player called by Game, direcion 0-7, bool enemy moveable
    bool moveHero(int, bool);
    // Player attack neighbour enemy from given direction, bool enemy moveable
    void attackNeighbour(int, bool);
    // Player consume neighbour potion from given direction, bool enemy moveable
    void consumePotion(int, bool);
   
    // Return action info content;
    std::string getAction();

    friend std::ostream &operator<<(std::ostream &out, const Floor &f);
};

#endif
