#include "block.h"

Block::Block(double x,double y,char value,string orientation):Tile(x,y,value)
{
    itsXOld=x;
    itsOrientation=orientation;
    itsYOld=y;
    itsTileImage.load(":pad.png");
    Q_ASSERT(!itsTileImage.isNull());
}

void Block::draw(QPainter *aPainter,int value)
{

    itsTileImage= itsTileImage.scaled(QSize(96,48));
    aPainter->drawImage(itsX,itsY,itsTileImage);
}

void Block::move(int i)
{
    if(itsOrientation=="FALL")
    {
        if(sens=="")
        {
            sens="descend";
        }
        if(sens=="descend")
        {
            itsY+=i;
            if(itsY>=itsYOld+96)
            {
              sens="monte";
            }

        }
        if(sens=="monte")
        {
           itsY-=i;
           if(itsY<=itsYOld-240)
           {
                sens="descend";
           }

        }
        /*else
        {
            itsY+=i;
            sens="descend";
        }*/

    }
    else if(itsOrientation=="SLIDE")
    {
        if(sens=="gauche")
        {
            itsX-=i;
            if(itsX<=itsXOld-96)
            {
              sens="droite";
            }

        }
        if(sens=="droite")
        {
           itsX+=i;
           if(itsX>=itsXOld+96)
           {
                sens="gauche";
           }

        }
        else
        {
            itsX-=i;
            sens="gauche";
        }
    }
    else if(itsOrientation=="POP")
    {
        if(getRect().y()==itsYOld && timer==100)
        {
            setY(400);
            timer=0;
        }
        else if(getRect().y()!=itsYOld && timer>=100)
        {
            setY(-400);
            timer=0;
        }
        else
        {
            timer++;
        }
    }
}
void Block::setXOld(double x)
{
   itsXOld-=(x*48);
}

