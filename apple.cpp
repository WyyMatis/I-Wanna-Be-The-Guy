#include "apple.h"

Apple::Apple(double x, double y, char value, string orientation):Tile(x,y,value)
{
    itsOrientation=orientation;
    itsTileImage.load(":pomme.png");
    Q_ASSERT(!itsTileImage.isNull());
    itsXOld=x;
    itsYOld=y;
}

void Apple::move(int i)
{
    if(itsOrientation=="FALL")
    {
        itsY+=i;
    }
    else if(itsOrientation=="UP")
    {
        itsY-=i;
    }
}
bool Apple::getFalling()
{
    return isFalling;
}
void Apple::setFalling(bool aBool)
{
    isFalling=aBool;
}
