#include "personn.h"
#include "personn.h"

void Personn::setItsSpeed(int value)
{
    itsSpeed = value;
}

bool Personn::getDoubleJump()
{
    return doubleJump;
}

void Personn::setDoubleJump(bool jump)
{
    doubleJump=jump;
}

void Personn::setJump(bool value)
{
    isJumping=value;
}
void Personn::resetV_y()
{
    v_y=v_saut;
}
void Personn::jump()
{
    if(v_y>0)
    {
        isJumping=false;
    }
    itsY += v_y;
    v_y += v_grav;
}

void Personn::fall()
{
    isJumping=false;
    if(v_y<0)v_y=0;
    v_y+=v_grav;
    itsY+=v_y;
}

void Personn::stopJump()
{
    if(!isFalling)v_y=0;
}

int Personn::intersect(vector<vector<Tile *>> aLevel,int nbLigne,int nbColonne)
{
    bool aBool=false,touch=false,touch2=false;
    int beDead=0;
    string solid="abcdefmzXYWLKINOPQ";
    string piege="2345678";
    int isSpike=0;
    for(int i=0;i<nbLigne;i++)
        {
            for(int j=0;j<nbColonne;j++)
            {
                    for(int nb=0;nb<18;nb++)
                    {
                        if(aLevel[i][j]->getValue()==solid[nb])
                        {
                         touch=true;
                        }
                    }
                    for(int nb=0;nb<7;nb++)
                    {
                        if(aLevel[i][j]->getValue()==piege[nb])
                        {
                            if(piege[nb]=='2' ||piege[nb]=='3' ||piege[nb]=='4' ||piege[nb]=='5')
                            {
                                isSpike=piege[nb]-'0';
                            }
                         touch2=true;
                        }
                    }
                    if(touch2)
                    {
                        if(getRect().intersects(aLevel[i][j]->getRect()) && isSpike == 0)
                        {

                            beDead=1;
                        }
                        else if(isSpike !=0)
                        {
                            QRect rectVerif1,rectVerif2,rectVerif3;
                            switch (isSpike)
                            {
                                case 2:rectVerif1.setRect(aLevel[i][j]->getRect().x(),aLevel[i][j]->getRect().y()+47,1,1);
                                rectVerif2.setRect(aLevel[i][j]->getRect().x()+24,aLevel[i][j]->getRect().y(),1,1);
                                rectVerif3.setRect(aLevel[i][j]->getRect().x()+47,aLevel[i][j]->getRect().y()+47,1,1);;
                                break;
                                case 3:rectVerif1.setRect(aLevel[i][j]->getRect().x()+47,aLevel[i][j]->getRect().y(),1,1);
                                rectVerif2.setRect(aLevel[i][j]->getRect().x()+24,aLevel[i][j]->getRect().y()+47,1,1);
                                rectVerif3.setRect(aLevel[i][j]->getRect().x(),aLevel[i][j]->getRect().y(),1,1);;
                                break;
                                case 4:rectVerif1.setRect(aLevel[i][j]->getRect().x(),aLevel[i][j]->getRect().y(),1,1);
                                rectVerif2.setRect(aLevel[i][j]->getRect().x()+47,aLevel[i][j]->getRect().y()+24,1,1);
                                rectVerif3.setRect(aLevel[i][j]->getRect().x(),aLevel[i][j]->getRect().y()+47,1,1);;
                                break;
                                case 5:rectVerif1.setRect(aLevel[i][j]->getRect().x()+47,aLevel[i][j]->getRect().y(),1,1);
                                rectVerif2.setRect(aLevel[i][j]->getRect().x(),aLevel[i][j]->getRect().y()+24,1,1);
                                rectVerif3.setRect(aLevel[i][j]->getRect().x()+47,aLevel[i][j]->getRect().y()+47,1,1);;
                            };
                            if(getRect().intersects(rectVerif1)||getRect().intersects(rectVerif2)||getRect().intersects(rectVerif3) )
                            {
                                beDead=1;
                            }
                        }
                        touch2=false;
                        isSpike=false;
                    }
                    if(touch && beDead!=1)
                    {
                        //sensé vérifié si touche bloc à ma droite
                        if(getRect().intersects(aLevel[i][j]->getRect()) && !aBool
                                && getRect().x()+getRect().width()>=aLevel[i][j]->getRect().x() && getRect().x()+getRect().width()<=aLevel[i][j]->getRect().x()+aLevel[i][j]->getRect().width()/2
                                && (getRect().y()>=aLevel[i][j]->getRect().y()-48 && getRect().y()<aLevel[i][j]->getRect().y()+48)
                                )
                        {
                            /*isFalling=false;
                            inAir=false;
                            beDead=2;
                            aBool=true;*/
                           if(j+1<nbColonne && j-1>=0 && i-1>=0 && i+1<nbLigne)
                            {
                                /*if(aLevel[i-1][j-1]->getValue()!='0')
                                {
                                    isFalling=true;
                                    isJumping=false;
                                    aBool=true;
                                }*/
                                if(aLevel[i+1][j-1]->getValue()!='0')
                                {

                                    isFalling=false;
                                    inAir=false;
                                }
                                else
                                {

                                    inAir=true;
                                    isFalling=true;
                                }

                                beDead=2;
                                aBool=true;
                                if(aBool)
                                {
                                    aBool=true;
                                }

                            }
                        }
                        //sensé vérifié si touche bloc à ma gauche
                        else if(getRect().intersects(aLevel[i][j]->getRect()) && !aBool
                                && getRect().x()<=aLevel[i][j]->getRect().x()+aLevel[i][j]->getRect().width()
                                && (getRect().y()>=aLevel[i][j]->getRect().y()-23 && getRect().y()<aLevel[i][j]->getRect().y()+48)
                                )
                        {
                            /*isFalling=false;
                            beDead=3;
                            inAir=false;
                            aBool=true;*/
                            if(j+1<nbColonne && j-1>=0 && i-1>=0 && i+1<nbLigne)
                            {
                                if(aLevel[i+1][j+1]->getValue()!='0')
                                {

                                    isFalling=false;
                                    inAir=false;
                                    aBool=true;

                                }
                                else
                                {

                                    inAir=true;
                                    isFalling=true;
                                }
                                beDead=3;

                                /*aBool=true;
                                if(aBool)
                                {
                                    aBool=true;
                                }*/
                            }

                        }
                        //verifie si bloc au-dessus tête
                        if(getRect().intersects(aLevel[i][j]->getRect()) && aLevel[i][j]->getRect().y()<itsY)
                        {
                            if(!aBool)
                            {
                                isFalling=true;
                                isJumping=false;
                                aBool=true;
                            }

                        }
                        //détecte le block sous mes pieds
                        if(getRect().intersects(aLevel[i][j]->getRect()) && !aBool && aLevel[i][j]->getRect().y()>itsY)
                        {
                            itsY=aLevel[i][j]->getRect().y()-47;
                            isFalling=false;
                            inAir=false;
                            aBool=true;
                        }




                        if(!aBool)
                        {
                            isFalling=true;
                            inAir=true;
                        }
                        touch=false;
                    }
                }
            }
    return beDead;
}

Personn::Personn()
{
    itsX=2*48;
    itsY=428;
    itsWidth=48;
    itsHeight=49;
    itsSpeed=0;
    v_saut=-10;
    v_grav=0.2;
    v_y=v_saut;
    isJumping=false;
    isFalling=false;
    inAir=false;
    doubleJump=false;
    itsPersonn.load("../protoV4/mario.png");
}

void Personn::draw(QPainter *aPainter,int value)
{
    if(!inAir)
    {
        if(value==0)
        {
            itsPersonn.load(":mario.png");
        }
        else if(value==37)
        {
            itsPersonn.load(":mariocour.png");
        }
        else if(value==75)
        {
            itsPersonn.load(":mariocour2.png");
        }
        else if(value==113)
        {
            itsPersonn.load(":mariocour.png");
        }
    }
    else
    {
        itsPersonn.load(":marioJump.png");
    }
    Q_ASSERT(!itsPersonn.isNull());
    itsPersonn = itsPersonn.scaled(QSize(48,48));
    if(itsDirection)
    {
         aPainter->drawImage(itsX,itsY,itsPersonn.mirrored(1,0));
    }
    else
    {
       aPainter->drawImage(itsX,itsY,itsPersonn);
    }

}

void Personn::setItsDirection(bool direction)
{
    itsDirection=direction;
}

int Personn::calculatePosition()
{
    itsX=itsX+itsSpeed;
    if(isJumping)jump();
    if(isFalling and !isJumping)fall();
    /*if(inAir and !doubleJump and isJumping)
    {
        jump();
        fall();
        doubleJump=true;
    }*/
    return itsY;
}
bool Personn::getInAir()
{
    return inAir;
}

void Personn::setSpeed(int aSpeed)
{
    itsSpeed=aSpeed;
}
