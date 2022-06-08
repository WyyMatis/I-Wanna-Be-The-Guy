#ifndef LIGHTNING_H
#define LIGHTNING_H


#include "tile.h"
class Lightning: public Tile
{
private:
    bool isFalling;
    bool isVisible;
    int oldY;
public:
    Lightning(double x,double y,char value,bool visible);
    void draw(QPainter *aPainter,int value);
    void move(int i);
    bool getFalling();
    void setFalling(bool aBool);
};

#endif // LIGHTNING_H
