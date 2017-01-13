#include <iostream>
#include "textdisplay.h"
#include "cell.h"
#include "posn.h"
using namespace std;

TextDisplay::TextDisplay() {
  for (int i = 0; i < 25; i++) {
    vector<char> theRow;
    for (int j = 0; j < 79; j++) {
      theRow.emplace_back('_');
    }
    theDisplay.emplace_back(theRow);
  }
}

void TextDisplay::notify(Cell &whoNotified) {
  int r = whoNotified.getCoords().row;
  int c = whoNotified.getCoords().col;
  char symb = whoNotified.getSymbol();
  theDisplay[r][c] = symb;
}

TextDisplay::~TextDisplay() {}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 79; j++) {
      out << td.theDisplay[i][j];
    }
    out << endl;
  }     
  return out;
}
