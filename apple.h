#ifndef APPLE_H
#define APPLE_H

#include "tile.h"
class Apple: public Tile
{
private:
    bool isFalling;
    string itsOrientation;
    double itsXOld;
    double itsYOld;
    string sens;

public:
    Apple(double x,double y,char value,string orientation);
    void move(int i);
    bool getFalling();
    void setFalling(bool aBool);
};

#endif // APPLE_H
