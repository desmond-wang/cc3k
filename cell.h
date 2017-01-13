#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include <vector>
#include <memory>
#include "character.h"
#include "item.h"

class Posn;
class TextDisplay;

class Cell {

    int row, col;
    char symb;
    // ptr to a Player or Enemy
    std::shared_ptr<Character> charPtr; 
    // ptr to a Gold or a Potion
    std::shared_ptr<Item> itemPtr;
    // 8 neighbours the the cell
    std::vector<std::shared_ptr<Cell>> neighbours;
    // TextDisplay
    std::shared_ptr<TextDisplay> td;
    

public:
    Cell();
    ~Cell();
    
    // Sets the row and column number
    void setCoords(int, int);
    // Returns row and column number.
    Posn getCoords() const;

    // Sets the char symbol and notify TextDisplay.
    void setSymbol(char);
    // Returns the char symbol
    char getSymbol();
  
    // Set ptr of the Gold or a Potion
    void setItem(std::shared_ptr<Item>);
    // Set ptr of the Player or Enemy
    void setCharacter(std::shared_ptr<Character>);

    // Return Iterm or Character pointer
    std::shared_ptr<Item> getItem();        
    std::shared_ptr<Character> getCharacter();

    // Add one neighbour cell each time 
    void attchNeighbour(std::shared_ptr<Cell>);
    // Set TextDisplay pointer
    void setTextDisplayPtr(std::shared_ptr<TextDisplay>);
    // Return the neighbour array
    std::vector<std::shared_ptr<Cell>> getNeighbours();
    // Return a random cell pointer of available neighbour tile
    std::shared_ptr<Cell> randomNbCellPtr();

};
#endif
