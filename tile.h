#ifndef TILE_H
#define TILE_H


#include <QRect>
#include <iostream>

#include <QPainter>
using namespace std;
class Tile{
private:

    int itsWidth;
    int itsHeight;
    int itsSpeed;
    int itsValue;
    bool isFalling;
    string itsSens;
    double itsXOld;
protected:
    double itsX;
    double itsY;
    QImage itsTileImage;
public:
    Tile(double x,double y,char value);
    virtual ~Tile();
    void setX(char x);
    void setY(int x);
    void setSpeed(int aSpeed);
    void calculatePosition(double value);
    virtual QRect getRect();
    virtual void draw(QPainter *aPainter,int value);
    void setValue(char value);
    char getValue();
    virtual void move(int i);
    virtual bool getFalling();
    virtual void setFalling(bool aBool);
    virtual string getSens();

   virtual void setXOld(double x);
};

#endif // TILE_H
