#include <fstream>
#include <sstream>
#include "floor.h"
#include "character.h"
#include "shade.h"
#include "enemy.h"

using namespace std;

extern PRNG prng1;


Floor::Floor() {
    td = make_shared<TextDisplay>();
}

Floor::~Floor() {}

void Floor::setHeroPosn(Posn p) {
    heroPosn = p;
}

string Floor::getAction(){
    return action;
}

vector<vector<Posn>> Floor::getChamberTiles() {
    return chamberTiles;
}   

shared_ptr<Cell> Floor::getCell(Posn p) {
    return theFloor[p.row][p.col];
}   


//---INITIALIZATION----------
//###########################
void Floor::init(string name, shared_ptr<Player> playPtr, int floorNumber) {

    ifstream fileIn{name};
    theFloor.clear();
    string whiteSpace;
    curSymbol = '.'; //+, #, G
    nextSymbol = '.';

    // dragonHoard list save for init Dragon
    vector<shared_ptr<Cell>> dHoard;

    for (int floor = 0; floor < floorNumber-1; floor++) {
        // go down 26 lines
        for (int l = 0; l < 25; l++) {
            getline(fileIn,whiteSpace);
        }
    }

    for (int i = 0; i < 25; i++) {
        vector<shared_ptr<Cell>> theRow;
        for (int j = 0; j < 79; j++) {
            shared_ptr<Cell> cptr = make_shared<Cell>();
            cptr->setCoords(i,j);
            cptr->setTextDisplayPtr(td);
            char symb;
            fileIn.get(symb);
            // init player
            if (symb == '@') {
                //shared_ptr<Character> heroPtr = make_shared<Shade>();
                cptr->setCharacter(playPtr);
                heroPosn.row = i;
                heroPosn.col = j;
            // init enemies (not Dragon)
            } else if (symb == 'H' || symb == 'W' || symb == 'L' || 
                       symb == 'E' || symb == 'O' || symb == 'M'){
                EnemyType race = static_cast<EnemyType>(symb);
                shared_ptr<Character> enemyPtr = make_shared<Enemy>(race);
                cptr->setCharacter(enemyPtr);                
            } else if (symb >= '0' && symb <= '5') {
                shared_ptr<Potion> potionPtr;
                if (symb == '0') {
                    potionPtr = make_shared<PotionRH>();//(PotionType::RH);
                } else if (symb == '1') {
                    potionPtr = make_shared<PotionBA>();//(PotionType::BA);
                } else if (symb == '2') {
                    potionPtr = make_shared<PotionBD>();//(PotionType::BD);
                } else if (symb == '3') {
                    potionPtr = make_shared<PotionPH>();//(PotionType::PH);
                } else if (symb == '4') {
                    potionPtr = make_shared<PotionWA>();//(PotionType::WA);
                } else {
                    potionPtr = make_shared<PotionWD>();//(PotionType::WD);
                }
                cptr->setItem(potionPtr);
                symb = 'P';
            } else if (symb >= '6' && symb <= '9') {
                shared_ptr<Gold> treasurePtr;
                if (symb == '9') {
                    dHoard.emplace_back(cptr);
                    // add to dragonHoard list
                    treasurePtr = make_shared<Gold>(GoldType::dragonHoard);
                } else if (symb == '8') {
                    treasurePtr = make_shared<Gold>(GoldType::merchantHoard);
                } else if (symb == '7') {
                    treasurePtr = make_shared<Gold>(GoldType::small);
                } else {
                    treasurePtr = make_shared<Gold>(GoldType::normal);
                }
                cptr->setItem(treasurePtr);
                symb = 'G';
            }
            cptr->setSymbol(symb);
            theRow.emplace_back(cptr);
        }
        getline(fileIn,whiteSpace);
        theFloor.emplace_back(theRow);
    }
    addNeighbours();
    
    //init Dragons
    int size = dHoard.size();
    for (int k = 0; k < size; k++) {
        shared_ptr<Cell> curCell = dHoard[k];
        shared_ptr<Gold> goldPtr = dynamic_pointer_cast<Gold>(curCell->getItem());
        shared_ptr<Cell> nbCell;
        for (int i = 0; i < 8; i++) {
            nbCell = curCell->getNeighbours()[i];
            if (nbCell->getSymbol() == 'D') {
                shared_ptr<Character> dragonPtr = make_shared<Enemy>(EnemyType::dragon, goldPtr);
                nbCell->setCharacter(dragonPtr);
            }
        }
    }
}

void Floor::addNeighbours() {
    for (int i = 2; i < 23; i++) {
        for (int j = 2; j < 77; j++) {
            theFloor[i][j]->attchNeighbour(theFloor[i-1][j-1]);
            theFloor[i][j]->attchNeighbour(theFloor[i-1][j]);
            theFloor[i][j]->attchNeighbour(theFloor[i-1][j+1]);
            theFloor[i][j]->attchNeighbour(theFloor[i][j+1]);
            theFloor[i][j]->attchNeighbour(theFloor[i+1][j+1]);
            theFloor[i][j]->attchNeighbour(theFloor[i+1][j]);
            theFloor[i][j]->attchNeighbour(theFloor[i+1][j-1]);
            theFloor[i][j]->attchNeighbour(theFloor[i][j-1]);
        }
    }
}

void Floor::initDefault() {
    string name = "defaultMap.txt";
    ifstream fileIn{name};
    theFloor.clear();
    chamberTiles.clear();
    curSymbol = '.'; 
    nextSymbol = '.';

    string whiteSpace;
    vector<Posn> v0,v1,v2,v3,v4;
    for (int i = 0; i < 25; i++) {
        vector<shared_ptr<Cell>> theRow;
        for (int j = 0; j < 79; j++) {
            shared_ptr<Cell> cptr = make_shared<Cell>();
            cptr->setCoords(i,j); 
            cptr->setTextDisplayPtr(td);
            char symb;
            fileIn.get(symb);
            cptr->setSymbol(symb);
            
            //init chamber number
            if (i > 2 && i < 7 && j > 2 && j < 29 && symb == '.') {
                Posn cTile{i,j};
                v0.emplace_back(cTile);
            }
            if (i > 2 && i < 7 && j > 38 && j < 73 && symb == '.') {
                Posn cTile{i,j};
                v1.emplace_back(cTile);
            }
            if (i > 6 && i < 13 && j > 60 && j < 76 && symb == '.') {
                Posn cTile{i,j};
                v1.emplace_back(cTile);
            }
            if (i > 9 && i < 13 && j > 37 && j < 50 && symb == '.') {
                Posn cTile{i,j};
                v2.emplace_back(cTile);
            }
            if (i > 14 && i < 22 && j > 3 && j < 25 && symb == '.') {
                Posn cTile{i,j};
                v3.emplace_back(cTile);
            }
            if (i > 15 && i < 22 && j > 36 && j < 76 && symb == '.') {
                Posn cTile{i,j};
                v4.emplace_back(cTile);
            } 
            
            theRow.emplace_back(cptr);   
        }
        
        //skip whitespace after last '|'
        getline(fileIn,whiteSpace);
        theFloor.emplace_back(theRow);
    }
    chamberTiles.emplace_back(v0);
    chamberTiles.emplace_back(v1);
    chamberTiles.emplace_back(v2);
    chamberTiles.emplace_back(v3);
    chamberTiles.emplace_back(v4);
    addNeighbours();
}

//---PLAYER MOVE----------
void Floor::notifyNeighbours(shared_ptr<Cell> curCell, bool b) {
    shared_ptr<Cell> nbCell;
    char enemyType;
    int potionCounter = 0;
    string addToAction = "";
    for (int i = 0; i < 8; i++) {
        nbCell = curCell->getNeighbours()[i];
        enemyType = nbCell->getSymbol();
 
        if (enemyType == 'H'|| enemyType == 'W'|| enemyType == 'E'|| enemyType == 'O'|| 
            enemyType == 'M'|| enemyType == 'D'|| enemyType == 'L') {

            dynamic_pointer_cast<Enemy>(nbCell->getCharacter())->setCombatState(true);
        }

        if (b == true && enemyType == 'P'){
            potionCounter++;
        }
    }
    if (b == true && potionCounter == 0) {
        addToAction= ".";
    } else if (potionCounter == 1) {
        addToAction= " and sees 1 unknown potion. ";
    } else if (potionCounter > 1) {
        addToAction= " and sees "+ to_string(potionCounter) + " unknown potions. ";
    }
    action += addToAction;
}

string Floor::moveDirction(int dir){ 
    //translate 0-7 to string direction for showing in action info
    string moveIndex;
    if (dir == 0){
        moveIndex = "Northwest";
    } else if (dir == 1){
        moveIndex = "North";
    } else if (dir == 2){
        moveIndex = "Northeast";
    } else if (dir == 3){
        moveIndex = "East";
    } else if (dir == 4){
        moveIndex = "Southeast";
    } else if (dir == 5){
        moveIndex = "South";
    } else if (dir == 6){
        moveIndex = "Southwest";
    } else {
        moveIndex = "West";
    }
    return moveIndex;
}

bool Floor::moveHero(int direction, bool isEnemyMove) {

    action = ""; //initialize action info
    curSymbol = nextSymbol;

    int row = heroPosn.row;
    int col = heroPosn.col;
    shared_ptr<Cell> curCell = theFloor[row][col];
    shared_ptr<Cell> nbCell = (curCell->getNeighbours())[direction];
    char nbSymb = nbCell->getSymbol();

    if (nbSymb == '\\') {
        // reach stair, to change floor or restart
        return true;
    }

    if (nbSymb == '.' || nbSymb == 'G'|| nbSymb == '+'|| nbSymb == '#') {
    //check the tile which could be walked on
        nextSymbol = nbSymb;
        
        shared_ptr<Character> pcPtr = curCell->getCharacter();
        nbCell->setCharacter(pcPtr);
        nbCell->setSymbol(curCell->getSymbol());
        curCell->setCharacter(nullptr);
        heroPosn = nbCell->getCoords();

        if (nbSymb == 'G') {
            shared_ptr<Item> itemPtr = nbCell->getItem();
            shared_ptr<Gold> goldPtr = dynamic_pointer_cast<Gold>(itemPtr);
            if (goldPtr->isConsumable()) {
                shared_ptr<Player> playerPtr = dynamic_pointer_cast<Player>(pcPtr);
                playerPtr->consumeGold(*goldPtr);
                nbCell->setItem(nullptr);
            }
        }

        if (curSymbol == 'G' && curCell->getItem() == nullptr) {
            curSymbol = '.';
        }
        // if '+', '#', 'G'(Dragon) need setback
        curCell->setSymbol(curSymbol);

        //check Neighbours if there are any enemies
        action += ("PC moves " + moveDirction(direction));
        if (isEnemyMove) notifyNeighbours(nbCell, true);
    } else {
        errorMsg = "PC can not move there!";
        throw errorMsg;
    }
    return false; 
}


//---PLAYER ATTACK AND CONSUME----------
//######################################
void Floor::attackNeighbour(int direction, bool isEnemyMove) {
    // modify action string 
    action = "";
    int row = heroPosn.row;
    int col = heroPosn.col;
    shared_ptr<Cell> curCell = theFloor[row][col];
    shared_ptr<Cell> nbCell = (curCell->getNeighbours())[direction];
    char nbSymb = nbCell->getSymbol();

    if (nbSymb == 'H' || nbSymb == 'W'|| nbSymb == 'E'|| 
        nbSymb == 'O' || nbSymb == 'M'|| nbSymb == 'L'||
        nbSymb == 'D') {

        string actionInfo = curCell->getCharacter()->attack(*(nbCell->getCharacter()));
        action += actionInfo;
        if (isEnemyMove) notifyNeighbours(curCell, false);
    }else {
        errorMsg = "There is no enemy!";
        throw errorMsg;
    }
}

void Floor::consumePotion(int direction, bool isEnemyMove) {
    action = "";
    int row = heroPosn.row;
    int col = heroPosn.col;
    shared_ptr<Cell> curCell = theFloor[row][col];
    shared_ptr<Cell> nbCell = (curCell->getNeighbours())[direction];
    char nbSymb = nbCell->getSymbol();
    shared_ptr<Player> heroPtr = dynamic_pointer_cast<Player>(curCell->getCharacter());

    if (nbSymb == 'P') {
        shared_ptr<Potion> potionPtr = dynamic_pointer_cast<Potion>(nbCell->getItem());
        string actionInfo = heroPtr->consumePotion(potionPtr);  //strategy patern pass ptr
        action += actionInfo;
        nbCell->setItem(nullptr);
        nbCell->setSymbol('.');
        if (isEnemyMove) notifyNeighbours(curCell, false);
    }else {
        errorMsg = "There is no potion!";
        throw errorMsg;
    }
}

    
//---ENEMIES MOVE----------
//#########################
void Floor::moveEnemies() {
    
    // initializtion 
    int row = heroPosn.row;
    int col = heroPosn.col;
    shared_ptr<Character> playerPtr = theFloor[row][col]->getCharacter();
    shared_ptr<Enemy> enemyPtr;

    // initialize a char map for enemies to move
    enemyMoveMap.clear();
    for (int l = 0; l < 25; l++) {
        vector<char> theRow;
        for (int m = 0; m < 79; m++) { 
            theRow.emplace_back(theFloor[l][m]->getSymbol());
        }
        enemyMoveMap.emplace_back(theRow);
    }
    
    // scan char map for each enemy
    shared_ptr<Cell> curCell;
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 79; j++) {
            shared_ptr<Cell> curCell = theFloor[i][j]; // cell pointer in theFloor[i][j] 
            char curSymbol = enemyMoveMap[i][j]; // symbol from saved char map of theFloor[i][j]
            
            shared_ptr<Character> charPtr = curCell->getCharacter(); 
            enemyPtr = dynamic_pointer_cast<Enemy>(charPtr);

            if (curSymbol == 'H' || curSymbol == 'W' || curSymbol == 'E' || 
                curSymbol == 'O' || curSymbol == 'M' || curSymbol == 'L' || 
                curSymbol == 'D'){
                
                // remove dead enemies, reset cell and drop GOLD!!!
                shared_ptr<Cell> nbCell = curCell->randomNbCellPtr();
                // generate available neighbour tile for moving or droping Gold
                if ((charPtr->curState()).hp < 1 ) { 
                    char resetSymbol = '.';
                    if (curSymbol == 'D') {
                        enemyPtr->releaseGold();
                    } else if (curSymbol == 'M') {
                        shared_ptr<Gold> treasurePtr = make_shared<Gold>(GoldType::merchantHoard);
                        curCell->setItem(treasurePtr);
                        resetSymbol = 'G';
                    } else if (curSymbol == 'H') {
                        shared_ptr<Gold> treasurePtr1 = make_shared<Gold>(GoldType::normal);
                        shared_ptr<Gold> treasurePtr2 = make_shared<Gold>(GoldType::normal);
                        curCell->setItem(treasurePtr1);
                        resetSymbol = 'G';
                        nbCell->setItem(treasurePtr2);
                        nbCell->setSymbol(resetSymbol);
                    }
                    curCell->setSymbol(resetSymbol);
                    curCell->setCharacter(nullptr);                

                // move moveable enemies (not D)
                } else if (curSymbol != 'D' && (!enemyPtr->getCombatState())){
                    nbCell->setCharacter(curCell->getCharacter());
                    nbCell->setSymbol(curCell->getSymbol());
                    curCell->setCharacter(nullptr);
                    curCell->setSymbol('.');

                // enattact player
                } else if (enemyPtr->getCombatState()) {
                    action += charPtr->attack(*playerPtr);
                }
            }

        }
    }
}


ostream &operator<<(ostream &out, const Floor &f) {
    out << *(f.td);
    return out;
}


