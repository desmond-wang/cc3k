#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>

class Cell;

class TextDisplay {
  std::vector<std::vector<char>> theDisplay;

 public:
  TextDisplay();

  void notify(Cell &whoNotified);

  ~TextDisplay();

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
