#ifndef OBJECTS_H
#define OBJECTS_H
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <math.h>
#include "Animation.h"
#include "dest.h"
#include "Scoreboard.h"
using namespace sf;




class Entity : public Scoreboard
{
public:
float x,y,dx,dy,R,angle;
bool life;
std::string name;
Animation anim;

Entity()
{
  life=1;
}

void settings(Animation &a,int X,int Y,float Angle=0,int radius=1)
{
  anim = a;
  x=X; y=Y;
  angle = Angle;
  R = radius;
}

virtual void update(){};

void draw(RenderWindow &app)
{
  anim.sprite.setPosition(x,y);
  anim.sprite.setRotation(angle+90);
  app.draw(anim.sprite);

  CircleShape circle(R);
  circle.setFillColor(Color(255,0,0,170));
  circle.setPosition(x,y);
  circle.setOrigin(R,R);
  //app.draw(circle);
}

virtual ~Entity(){};
};


class asteroid: public Entity
{
public:
  asteroid()
  {
    dx=rand()%8-4;
    dy=rand()%8-4;
    name="asteroid";
  }

void  update()
  {
   x+=dx + power;
   y+=dy + power;

   if (x>W) x=0;  if (x<0) x=W;
   if (y>H) y=0;  if (y<0) y=H;
  }

};



class bullet: public Entity
{
public:
  bullet()
  {
    name="bullet";
  }

void  update()
  {
   dx=cos(angle*DEGTORAD)*6;
   dy=sin(angle*DEGTORAD)*6;
  // angle+=rand()%6-3;
   x+=dx;
   y+=dy;

   if (x>W || x<0 || y>H || y<0) life=0;
  }

};


class player: public Entity
{
public:
   bool thrust;

   player()
   {
     name="player";
   }

   void update()
   {
     if (thrust)
      { dx+=cos(angle*DEGTORAD)*0.2;
        dy+=sin(angle*DEGTORAD)*0.2; }
     else
      { dx*=0.99;
        dy*=0.99; }

    int maxSpeed=15;
    float speed = sqrt(dx*dx+dy*dy);
    if (speed>maxSpeed)
     { dx *= maxSpeed/speed;
       dy *= maxSpeed/speed; }

    x+=dx;
    y+=dy;

    if (x>W) x=0; if (x<0) x=W;
    if (y>H) y=0; if (y<0) y=H;
   }

};


bool isCollide(Entity *a,Entity *b)
{
  return (b->x - a->x)*(b->x - a->x)+
         (b->y - a->y)*(b->y - a->y)<
         (a->R + b->R)*(a->R + b->R);
}



 
 
#endif
