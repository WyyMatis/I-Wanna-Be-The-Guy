#ifndef BLOCK_H
#define BLOCK_H

#include "tile.h"

class Block:public Tile
{
private:
    double itsXOld;
    double itsYOld;
    string itsOrientation;
    string sens;
    int timer=0;
public:
    Block(double x,double y,char value,string orientation);
    void draw(QPainter *aPainter,int value);
    void move(int i);
    void setXOld(double x);
};

#endif // Block_H
