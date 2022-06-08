#ifndef PERSONN_H
#define PERSONN_H

#include <QRect>
#include <iostream>
#include <QImage>
#include <QPainter>
#include <vector>
#include "tile.h"
using namespace std;

class Personn
{
private:
    double itsX;
    double itsY;
    int itsWidth;
    int itsHeight;
    int itsSpeed;
    QImage itsPersonn;

    double v_y;
    double v_saut;
    double v_grav;
    bool isJumping;
    bool isFalling;
    bool inAir;
    bool doubleJump;
    bool itsDirection=false;

public:
    Personn();
    int calculatePosition();
    void setItsSpeed(int value);
    bool getDoubleJump();
    void setDoubleJump(bool jump);
    void draw(QPainter *aPainter,int value);
    void setItsDirection(bool direction);
    void setJump(bool value);
    void resetV_y();
    void jump();
    void fall();
    bool getFall(){return isFalling;};
    bool getJump(){return isJumping;};
    QRect getRect(){return QRect(itsX,itsY,itsWidth,itsHeight);};
    void stopJump();
    int intersect(vector<vector<Tile*>> aLevel,int nbLigne,int nbColonne);
    bool getInAir();
    void setSpeed(int aSpeed);
};

#endif // PERSONN_H
