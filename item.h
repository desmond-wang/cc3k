#ifndef item_h
#define item_h

class Item{ //has subclass Gold and Potion
protected:
    int value;
    
public:
    virtual int getValue() = 0;
    
};

#endif
