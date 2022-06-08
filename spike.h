#ifndef SPIKE_H
#define SPIKE_H
#include "tile.h"

class Spike: public Tile
{
private:
    bool isVisible;
public:
    Spike(double x,double y,char letter);
    void draw(QPainter *aPainter,int value);
};

#endif // Spike_H
