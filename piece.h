#ifndef PIECE_H
#define PIECE_H


#include "tile.h"

class Piece: public Tile
{
private:
    bool itsVisible;
    bool isLucky;
public:
    Piece(double x,double y,char value,bool lucky);
    bool getFalling();
    void draw(QPainter *aPainter,int value);
};
#endif // PIECE_H
