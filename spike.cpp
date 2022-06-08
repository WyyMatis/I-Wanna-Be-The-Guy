#include "spike.h"
#include <QPolygon>
Spike::Spike(double x,double y,char value):Tile(x,y,value)
{
    itsTileImage.load(":spike.png");
}

void Spike::draw(QPainter *aPainter,int value)
{
    if(getValue()=='2')
    {
        Q_ASSERT(!itsTileImage.isNull());
        itsTileImage= itsTileImage.scaled(QSize(48,48));
        aPainter->drawImage(itsX,itsY,itsTileImage);
    }

}
