#include "tile.h"
#include <iostream>
#include <QDebug>
using namespace std;
Tile::Tile(double x,double y,char value)
{
    itsX=x;
    itsXOld=x;
    itsY=y;
    itsWidth=48;
    itsHeight=48;
    itsSpeed=0;
    itsValue=value;
    isFalling=false;
    //itsTileImage.setRect(itsX,itsY,itsWidth,itsHeight);
    switch(itsValue)
    {
    case '0':itsTileImage.load(":vide.png");
        break;
    case 'a':itsTileImage.load(":sol.png");
        break;
    case 'b':itsTileImage.load(":littlesolleft.png");
        break;
    case 'c':itsTileImage.load(":littlesol.png");
        break;
    case 'd':itsTileImage.load(":littlesolright.png");
        break;
    case 'e':itsTileImage.load(":solright.png");
        break;
    case 'f':itsTileImage.load(":solleft.png");
        break;
    case 'g':itsTileImage.load(":grassleft.png");
        break;
    case 'h':itsTileImage.load(":grassmid.png");
        break;
    case 'i':itsTileImage.load(":grassright.png");
        break;
    case 'j':itsTileImage.load(":treeroot.png");
        break;
    case 'k':itsTileImage.load(":treebottom.png");
        break;
    case 'l':itsTileImage.load(":treemid.png");
        break;
    case 'm':itsTileImage.load(":treetop.png");
        break;
    case 'n':itsTileImage.load(":arrowleft.png");
        break;
    case 'o':itsTileImage.load(":1cloudleft.png");
        break;
    case 'p':itsTileImage.load(":1cloud.png");
        break;
    case 'q':itsTileImage.load(":1cloudright.png");
        break;
    case 'r':itsTileImage.load(":2cloudleft.png");
        break;
    case 's':itsTileImage.load(":2cloudmid1.png");
        break;
    case 't':itsTileImage.load(":2cloudmid2.png");
        break;
    case 'u':itsTileImage.load(":2cloudmid3.png");
        break;
    case 'v':itsTileImage.load(":cloudbottomright.png");
        break;
    case 'w':itsTileImage.load(":cloudbottomleft.png");
        break;
    case 'x':itsTileImage.load(":cloudbottom.png");
        break;
    case 'y':itsTileImage.load(":cloudfill.png");
        break;
    case 'z':itsTileImage.load(":stone.png");
        break;
    case 'A':itsTileImage.load(":barrierleft.png");
        break;
    case 'B':itsTileImage.load(":barriermid.png");
        break;
    case 'C':itsTileImage.load(":barrierright.png");
        break;
    case 'D':itsTileImage.load(":signleft.png");
        break;
    case 'E':itsTileImage.load(":signmid.png");
        break;
    case 'F':itsTileImage.load(":signright.png");
        break;
    case 'G':itsTileImage.load(":trunk.png");
        break;
    case 'H':itsTileImage.load(":signstick.png");
        break;
    case 'I':itsTileImage.load(":sol_solo_grand.png");
        break;
    case 'J':itsTileImage.load(":cloud_cote_droit.png");
        break;
    case 'K':itsTileImage.load(":sol_cote_droit.png");
        break;
    case 'L':itsTileImage.load(":herbe_coin_droit.png");
        break;
    case 'M':itsTileImage.load(":treetop.png");
        break;
    case 'N':itsTileImage.load(":sol_cote_gauche.png");
        break;
    case 'O':itsTileImage.load(":sol_coin_droit_bas.png");
        break;
    case 'P':itsTileImage.load(":sol_coin_gauche_bas.png");
        break;
    case 'Q':itsTileImage.load(":sol_bas.png");
        break;
    case 'R':itsTileImage.load(":treetop.png");
        break;
    case 'S':itsTileImage.load(":arrowup.png");
        break;
    case 'T':itsTileImage.load(":arrowdown.png");
        break;
    case 'U':itsTileImage.load(":arrowright.png");
        break;
    case '?':itsTileImage.load(":flag1.png");
        break;
    case 'Z':itsTileImage.load(":flag1.png");
    /*    break;
    case '6':itsTileImage.load(":flag.png");
        break;
    case '7':itsTileImage.load(":flag.png");
        break;
    case '8':itsTileImage.load(":flag.png");
        break;
    case '9':itsTileImage.load(":flag.png");
        break;*/
    }
}

Tile::~Tile()
{

}

void Tile::setX(char x)
{
    int newStart=x-'0';
    itsX+=(newStart*48);
}

void Tile::setY(int x)
{
    itsY-=x;
}

void Tile::setSpeed(int aSpeed)
{
    itsSpeed=aSpeed;
}
void Tile::calculatePosition(double value)
{
    if(getValue()=='X')
    {
        setXOld(value);
    }
    itsX= itsX -(value*48);
}
void Tile::draw(QPainter * aPainter,int value)
{
    if(getValue()=='Z' || getValue()=='?')
    {
        if(value==0)
        {
            itsTileImage.load(":flag1.png");
        }
        else if(value==18 || value==128)
        {
            itsTileImage.load(":flag2.png");
        }
        else if(value==36 || value==110)
        {
            itsTileImage.load(":flag3.png");
        }
        else if(value==55 || value==91)
        {
            itsTileImage.load(":flag4.png");
        }
        else if(value==73)
        {
            itsTileImage.load(":flag5.png");
        }
    }
    Q_ASSERT(!itsTileImage.isNull());
    itsTileImage= itsTileImage.scaled(QSize(48,48));
    aPainter->drawImage(itsX,itsY,itsTileImage);
}

void Tile::setValue(char value)
{
    itsValue=value;
}

char Tile::getValue()
{
    return itsValue;
}
bool Tile::getFalling()
{
    return isFalling;
}

void Tile::move(int i)
{

}
void Tile::setFalling(bool aBool)
{
    isFalling=aBool;

}
QRect Tile::getRect()
{
    QRect TileBis;
    if(getValue()=='X' || getValue()=='Y' || getValue()=='W')
    {
        TileBis.setRect(itsX,itsY,itsWidth+48,itsHeight);
    }
    else if(getValue()=='8')
    {
        TileBis.setRect(itsX,itsY,itsWidth,itsHeight+48);
    }
    else
    {
        TileBis.setRect(itsX,itsY,itsWidth,itsHeight);
    }
    return TileBis;
}
string Tile::getSens()
{
    return itsSens;
}

void Tile::setXOld(double x)
{
    itsXOld-=(x*48);
}
