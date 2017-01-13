#include <fstream>
#include <iostream>
#include <iomanip>
#include "game.h"

using namespace std;

extern PRNG prng1;


Game::Game(){}
Game::~Game(){}


 /* ############################# Initial Helper ####################### */

ChamberAndPosn Game::initRandom() { 
    // generate a random poson in ramdom cell, and return a struct called ChamberAndPosn, 
    // which is the chamber number of this positon for futher use and the cell corrodinate.
    
    int chambersize = static_cast<int>((fl.getChamberTiles()).size());//get chamber vector
    int chamber = prng1(chambersize-1); //get random number
    int tileSize = static_cast<int>((fl.getChamberTiles())[chamber].size());
    int tile = prng1(tileSize-1);// get random number
    Posn pos = fl.getChamberTiles()[chamber][tile]; //get Posn
    ChamberAndPosn CandP {chamber, pos};
    return CandP;
}

char Game::randomNpc() {
    int probility = 18;
    int npcIndex = prng1(probility-1);
    if (npcIndex <= 4){
        return 'H';
    } else if (npcIndex >= 5 && npcIndex <= 7){
        return 'W';
    } else if (npcIndex >= 8 && npcIndex <= 12){
        return 'L';
    } else if (npcIndex == 13 || npcIndex == 14) {
        return 'E';
    } else if (npcIndex == 15 || npcIndex == 16) {
        return 'O';
    } else {
        return 'M';
    }
}


shared_ptr<Cell> Game::availableTile() {
    auto cellPtr = fl.getCell(initRandom().pos);
    while(!(cellPtr->getSymbol() == '.')){
        cellPtr = fl.getCell(initRandom ().pos);
    }
    return cellPtr;
}

void Game::initNpc() {
    for (int i = 0; i < 20; ++i){
        char raceChar= randomNpc();
        EnemyType race = static_cast<EnemyType>(raceChar);
        shared_ptr<Character> enemyPtr = make_shared<Enemy>(race);
        shared_ptr<Cell> cellptr = availableTile(); //floor has a method get cell pointer
        cellptr->setCharacter(enemyPtr);
        cellptr->setSymbol(raceChar);
    }
}


void Game::initPotion() {
    int counter = 0;
    while(counter <= 9){
    int potionIndex = prng1(5);
    shared_ptr<Potion> potionPtr;
    if (potionIndex == 0) {
        potionPtr = make_shared<PotionRH>();//(PotionType::RH); //consume string to differ the type
    } else if (potionIndex == 1) {
        potionPtr = make_shared<PotionBA>();//(PotionType::BA);
    } else if (potionIndex == 2) {
        potionPtr = make_shared<PotionBD>();//(PotionType::BD);
    } else if (potionIndex == 3) {
        potionPtr = make_shared<PotionPH>();//(PotionType::PH);
    }else if  (potionIndex == 4) {
        potionPtr = make_shared<PotionWA>();//(PotionType::WA);
    } else {
        potionPtr = make_shared<PotionWD>();//(PotionType::WD);
    }
    shared_ptr<Cell> cellPtr = availableTile();
    cellPtr->setItem(potionPtr);
    cellPtr->setSymbol('P');
    ++counter; //increase the counter for repeat initial
    }
}


void Game::initDragon (shared_ptr<Cell> goldCell, shared_ptr<Gold> goldPtr){
    shared_ptr<Cell> cellPtr = goldCell->randomNbCellPtr();
    //dragonPtr is making a enemy pointer (dragon, and given dragon gold pointer under enemy field).
    shared_ptr<Character> dragonPtr = make_shared<Enemy>(EnemyType::dragon, goldPtr);
    cellPtr->setCharacter(dragonPtr);
    cellPtr->setSymbol('D');
}



void Game::initGold(){
    int counter = 0;
    while(counter <= 9){
    
    int gold = prng1( 7 );
    shared_ptr<Gold> treasurePtr;
    if (gold <= 1) {
        treasurePtr = make_shared<Gold>(GoldType::small);
        
    } else if (gold > 1 && gold <= 6) {
        treasurePtr = make_shared<Gold>(GoldType::normal);
    }  else{
        treasurePtr = make_shared<Gold>(GoldType::dragonHoard);
        shared_ptr<Cell> cellPtr = availableTile();
        initDragon(cellPtr, treasurePtr);
        shared_ptr<Item> itemPtr = treasurePtr;
        cellPtr->setItem(itemPtr);
        cellPtr->setSymbol('G');
        ++counter;
        continue;
    }
    shared_ptr<Cell> cellPtr = availableTile();
    cellPtr->setItem(treasurePtr);
    cellPtr->setSymbol('G');
    ++counter;
    }
}


void Game::initPlayerPtr(){
    string race;    
    shared_ptr<Player> pc;
    printCover("cover.txt");
    
    while (true) {
        cin >> race;
        if (race == "s"){
            pc = make_shared<Shade>();
            playerRace = "Shade";
            break;
        } else if (race == "d"){
            pc = make_shared<Drow>();
            playerRace = "Drow";
            break;
        } else if (race == "v"){
            pc = make_shared<Vampire>();
            playerRace = "Vampire";
            break;
        } else if (race == "t"){
            pc = make_shared<Troll>();
            playerRace = "Troll";
            break;
        } else if (race == "g"){
            pc = make_shared<Goblin>();
            playerRace = "Goblin";
            break;
        } else {
            cout<<"Invalid player type, please enter again."<<endl;
        }
    }
    player = pc;
}


void Game::setPlayerAndStair(){
    ChamberAndPosn heroPos = initRandom();
    shared_ptr<Cell> heroCellPtr = fl.getCell(heroPos.pos); 
    //floor has a method get cell pointer
    heroCellPtr->setCharacter(player); 
    //change cell chraceter to pc(pointer)
    fl.setHeroPosn(heroPos.pos);
    heroCellPtr->setSymbol('@');
    //change the symbol of hero
    
    /* start to initial stair */
    
    int heroChamber = heroPos.chamber;
    ChamberAndPosn stairPos = initRandom();
    while (stairPos.chamber == heroChamber) {
        stairPos = initRandom();
    }
    shared_ptr<Cell> stairCellPtr = fl.getCell(stairPos.pos);
    stairCellPtr->setSymbol('\\');
}


 /* ####################  Public Initial method ####################### */

void Game::Init(string filename){   //pass file or empty overloading
    if (floorNum == 1) {
        isDefaultMap = false;
        fileName = filename;
        shared_ptr<Player> pc = make_shared<Shade>();
        player = pc;
        playerRace = "Shade";
    }
    fl.init(fileName, player, floorNum);  
    cout << fl << endl;
    string defaultAction = "Player character has spawned.";
    printStatus(defaultAction);
}

void Game::defaultInit(){
    isDefaultMap = true;
    if (floorNum == 1){
        initPlayerPtr();
    }
    fl.initDefault();
    setPlayerAndStair();
    initNpc();
    initGold();
    initPotion();
    cout << fl;
    string defaultAction = "Player character has spawned.";
    printStatus(defaultAction);
}


 /* ############################# Move Helper  ############################## */

void Game::attack(){
    string dir;
    cin >> dir;
    int move = moveIndex(dir);
    if (move >= 0) {
        fl.attackNeighbour(move, isEnemyMove);
    }
}


int Game::moveIndex(string dir){
    //right now, only helper function for attack (later for eat potion?)
    int moveIndex = -1;
    if (dir == "nw"){
        moveIndex = 0;
    } else if (dir == "no"){
        moveIndex = 1;
    } else if (dir == "ne"){
        moveIndex = 2;
    } else if (dir == "ea"){
        moveIndex = 3;
    } else if (dir == "se"){
        moveIndex = 4;
    } else if (dir == "so"){
        moveIndex = 5;
    } else if (dir == "sw"){
        moveIndex = 6;
    } else if (dir == "we"){
        moveIndex = 7;
    }
    return moveIndex;
}



void Game::eatPotion(){
    string dir;
    cin >> dir;
    int move = moveIndex(dir);
    if (move >= 0) {
        fl.consumePotion(move, isEnemyMove);
    }
}
void Game::printStatus(string actionContent){
    cout << "Race: " << playerRace << " Gold: "; 
    cout << setw(3) <<dynamic_pointer_cast<Player>(player)->getGold();
    cout << "                                               ";
    cout << "Floor " << floorNum << endl;
    cout << "HP: " << (player->curState()).hp << endl;
    cout << "Atk: " << (player->curState()).atk << endl;
    cout << "Def: " << (player->curState()).def << endl;
    cout << "Action: " << actionContent <<endl;
}


bool Game::isQuit(string gameStatus){
    //cout << "You " << gameStatus <<", enter r to restart or q to quit." << endl;
    if (gameStatus == "won") {
        printCover("coverWin.txt");
    } else {
        printCover("coverGameover.txt");
    }
    char input;
    while (cin >> input){ // check user input which user can only enter r or q.
        if (input == 'q'){
            return true;
        } else if (input == 'r'){
            return false;
        } else {
            cout << "Please enter correct instrcution!" << endl;
            continue;
        }
    }
    return true;
}

void Game::restartMap(){
    if (isDefaultMap == true){
        floorNum = 1;
        isEnemyMove = true;
        defaultInit();
    } else {
        floorNum = 1;
        isEnemyMove = true;
        Init(fileName);
    }
}

/* #######################  Public Move method ####################### */

void Game::start(){
    string move;
    int direction = -1;
    while(cin >> move){
        if (player->getPlayerType() == playerType::Troll){
            shared_ptr<Troll> troll = dynamic_pointer_cast<Troll>(player);
            troll->addHP();
        }
        if (move == "q"){
            cout << "You are defeated, program exit!" << endl;
            break;
        } else if (move == "r"){
            restartMap();
            continue;

        } else if (move == "f"){
	        if (isEnemyMove == true){
                isEnemyMove = false;
                cout << "Enemies stop!" << endl; 
	        } else {
	            isEnemyMove = true;
                cout << "Enemies move!" << endl;
	        }
            continue;

        } else if (move == "a"){
            try {
            attack();
            } catch (string error) {
                cout << error << endl;
                continue;
            } 

        } else if (move == "u"){
            try{
            eatPotion();
            } catch (string error) {
                cout << error << endl;
                continue;
            } 

        } else if (move == "nw" || move == "no" || move == "ne" || move == "ea" ||
                   move == "se" || move == "so" || move == "sw" || move == "we"){
            direction = moveIndex(move);
            try { 
            if(fl.moveHero(direction, isEnemyMove)) { //moveHero()
                if (floorNum == 5) {
                    bool quit = isQuit("won");
                    if (quit == true){//check if user enter q or r.
                        break;
                    } else {
                        restartMap();
                        continue;
                    }
                } else {
                    floorNum++;
                    if (isDefaultMap == true){
                        defaultInit();
                    } else {
                        Init(fileName);
                    }
                    continue;
                }   
            }
            } catch (string error) {
                cout << error << endl;
                continue;
            }
        }else { 
            cout << "Please enter correct instrcution!" << endl;
            continue;
        }

        if (isEnemyMove == true){
            fl.moveEnemies();
        }
        if ((player->curState()).hp < 1){
            bool quit = isQuit("lose"); //check if user enter q or r.
            if (quit == true){
                break;
                } else {
                    restartMap();
                    continue;
                }
        }

        cout << fl;
        printStatus(fl.getAction());
    }
}

            
void Game::printCover(std::string name) {
    
    vector<vector<char>> theCover;
    theCover.clear();
    string whiteSpace;
    ifstream fileIn{name};
    // scan name.txt
    for (int i = 0; i < 25; i++) {
        vector<char> theRow;
        for (int j = 0; j < 79; j++) {
            char symb;
            fileIn.get(symb);
            theRow.emplace_back(symb);
        }
        getline(fileIn,whiteSpace);
        theCover.emplace_back(theRow);
    }
    
    // print out theCover
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 79; j++) {
            cout << theCover[i][j];
        }
        cout << endl;
    }        
}    
 
