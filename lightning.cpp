#include "lightning.h"

Lightning::Lightning(double x, double y, char value,bool visible):Tile(x,y,value)
{
    isFalling=false;
    isVisible=visible;
    itsTileImage.load(":lightning1.png");
    Q_ASSERT(!itsTileImage.isNull());
    oldY=y;
}
void Lightning::draw(QPainter * aPainter,int value)
{
    if(isVisible)
    {
        Q_ASSERT(!itsTileImage.isNull());
        itsTileImage= itsTileImage.scaled(QSize(48,96));
        aPainter->drawImage(itsX,itsY,itsTileImage);
    }
}
void Lightning::move(int i)
{
   itsY+=i;
}

bool Lightning::getFalling()
{
    return isFalling;
}
void Lightning::setFalling(bool aBool)
{
    isFalling=aBool;
    isVisible=aBool;
    if(!isVisible)
    {
        itsY=oldY;

    }
}
