#include "cell.h"
#include "posn.h"
#include "PRNG.h"
#include "textdisplay.h"
using namespace std;

extern PRNG prng1;

Cell::Cell() {}

Cell::~Cell() {}

void Cell::setCoords(int r, int c) { row = r; col = c; }

Posn Cell::getCoords() const {
    Posn p {row, col};
    return p;
}

void Cell::setSymbol(char s) { 
    symb = s; 
    td->notify(*this);    
}

char Cell::getSymbol() {return symb; }

void Cell::attchNeighbour(shared_ptr<Cell> n) {
    neighbours.emplace_back(n);
}

vector<shared_ptr<Cell>> Cell::getNeighbours() {
    return neighbours;
}

void Cell::setItem(shared_ptr<Item> op){ itemPtr = op; }

void Cell::setCharacter(shared_ptr<Character> op) {
    charPtr = op;
}

shared_ptr<Item> Cell::getItem(){
    return itemPtr;
}

shared_ptr<Character> Cell::getCharacter() {
    return charPtr;
}

void Cell::setTextDisplayPtr(shared_ptr<TextDisplay> tdPtr) {
    td = tdPtr;    
}

shared_ptr<Cell> Cell::randomNbCellPtr() {
    int d = prng1(7); //get random number
    shared_ptr<Cell> nbCell = neighbours[d];
    while(!(nbCell->getSymbol() == '.')){
        d = prng1(7);
        nbCell = neighbours[d];
    }
    return nbCell;
}


