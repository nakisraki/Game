#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <list>
#include <math.h>
#include "Objects.h"
#include "Animation.h"
#include "Scoreboard.h"
#include "Sound.h"
#include "dest.h"
#include <string>
using namespace sf;
using namespace std;




Game::Game()
{

    t1.loadFromFile("images/spaceship.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/explosions/type_C.png");
    t4.loadFromFile("images/rock.png");
    t5.loadFromFile("images/fire_blue.png");
    t6.loadFromFile("images/rock_small.png");
    t7.loadFromFile("images/explosions/type_B.png");
    t8.loadFromFile("images/btitle.jpg");
    t1.setSmooth(true);
    t2.setSmooth(true);
    font.loadFromFile("images/space age.ttf");
    app = new RenderWindow(VideoMode(W, H), "LEXX");
    app->setFramerateLimit(60);
    background = new Sprite(t2);
    background_opt = new Sprite(t8);
    scoreboard = new Scoreboard(font,1,0);
    sExplosion = new Animation(t3, 0,0,256,256, 48, 0.5);
    sRock_small = new Animation(t6, 0,0,64,64, 16, 0.1);
    sBullet = new Animation(t5, 0,0,32,64, 16, 0.8);
    sPlayer_go = new Animation(t1, 40,40,40,40, 1, 0);
    sExplosion_ship = new Animation(t7, 0,0,192,192, 64, 0.5);
    sRock = new Animation(t4, 0,0,64,64, 16, 0.1);
    sPlayer = new Animation(t1, 40,0,40,40, 1, 0);
    sLifes = new Animation(t1,40,0,40,40,3,0);
     for(int i=0;i<15;i++)
    {
      asteroid *a = new asteroid();
      a->settings(*sRock, rand()%W, rand()%H, rand()%360, 25);
      entities.push_back(a);
    }

    p = new player();
    p->settings(*sPlayer,200,200,0,20);
    entities.push_back(p);
    lifes = 3;
    int add = 0;

    for(int i=0;i<4;i++)
    {
      Entity *pl = new Entity();
      pl->settings(*sLifes,-20+add,50,-88,20);
      plifes.push_back(pl);
      add+=45;
    }
    
    status = state[0];

    //bgmFile = "music/Tetris X BGM 01 (Technotris).ogg";
	square721.loadFromFile("images/space age.ttf");
	square721extended.loadFromFile("images/space age.ttf");
	menuRect = new RectangleShape();
	menuRect->setSize(sf::Vector2f(720.0f, 310.0f));
	menuRect->setFillColor(sf::Color(0, 0, 0, 155));
	menuRect->setPosition(440.0f, 380.0f);
	menuItems = new vector<sf::Text>;
   // menuItems->push_back(sf::Text("START : at level 0", square721extended, 50));
    //menuItems->push_back(sf::Text("OPTIONS", square721extended, 50));
    //menuItems->push_back(sf::Text("HIGH SCORES", square721extended, 50));
//
    string nm[3] = {"START","SETTINGS","HIGHSCORE"};
	for (int i = 0; i < 3; ++i)
	{
	    Text tex;
        tex.setFont(square721extended);
        tex.setString(nm[i]);
        tex.setCharacterSize(50);
        tex.setFillColor(i ? sf::Color::White : sf::Color::Cyan);
		tex.setStyle(sf::Text::Bold);
		tex.setOutlineThickness(2);
		tex.setOutlineColor(sf::Color::Black);
		tex.setPosition(450.0f, 400.0f + i*100);
		menuItems->push_back(tex);
	}

}


Game::~Game()
{

}


void Game::Loop()
{
    srand(time(0));
    Sounds sounds;
    Music music;
    music.openFromFile("sound/soundtrak.wav");
    music.setLoopPoints(sf::Music::TimeSpan(sf::seconds(52.646f), sf::seconds(49.180f)));
    music.setVolume(100.f);
    music.setLoop(true);
    music.play();

    /////main loop/////
    while (app->isOpen())
    {




       ///////NEW GAME

        Event event;
        while (app->pollEvent(event))
        {
           if (event.type == Event::Closed)
                app->close();

            if (event.type == Event::KeyPressed)
             if (event.key.code == Keyboard::Space)
              {
                bullet *b = new bullet();
                sounds.bullet.play();
                b->settings(*sBullet,p->x,p->y,p->angle,10);
                entities.push_back(b);
              }
        }


    if(status=="MENU"){
      if (Keyboard::isKeyPressed(Keyboard::Space)){
            status = "GAME";
            music.stop();
            }
      }

    if(status=="GAME"){
    if (Keyboard::isKeyPressed(Keyboard::Right)) p->angle+=3;
    if (Keyboard::isKeyPressed(Keyboard::Left))  p->angle-=3;
    if (Keyboard::isKeyPressed(Keyboard::Up)) p->thrust=true;
    else p->thrust=false;



    for(auto a:entities)
     for(auto b:entities)
    {
      if (a->name=="asteroid" && b->name=="bullet")
       if ( isCollide(a,b) )
           {
            a->life=false;
            b->life=false;
            scoreboard->updateScore(10);
            sounds.expl.play();

            Entity *e = new Entity();
            e->settings(*sExplosion,a->x,a->y);
            e->name="explosion";
            entities.push_back(e);


            for(int i=0;i<2;i++)
            {
             if (a->R==15) continue;
             Entity *e = new asteroid();
             e->settings(*sRock_small,a->x,a->y,rand()%360,15);
             entities.push_back(e);
            }

           }

      if (a->name=="player" && b->name=="asteroid")
       if ( isCollide(a,b) )
           {

            b->life=false;
            sounds.crash.play();
            lifes--;
            Entity *e = new Entity();
            e->settings(*sExplosion_ship,a->x,a->y);
            e->name="explosion";
            entities.push_back(e);

            p->settings(*sPlayer,W/2,H/2,0,20);
            p->dx=0; p->dy=0;
           }
    }


    if (p->thrust)  p->anim = *sPlayer_go;
    else   p->anim = *sPlayer;


    for(auto e:entities)
     if (e->name=="explosion")
      if (e->anim.isEnd()) e->life=0;

    int check = 0;
    if (rand()%150==0)
     {
       asteroid *a = new asteroid();
       a->settings(*sRock, 0,rand()%H, rand()%360, 25);
       entities.push_back(a);
     }

    for(auto i=entities.begin();i!=entities.end();)
    {
      Entity *e = *i;

      e->update();
      e->anim.update();

      if (e->life==false) {i=entities.erase(i); delete e;}
      else i++;
    }

    if(lifes>=0){
       plifes.resize(lifes+1);
    }

   if(lifes<0){
    app->close();
    status = "MENU";
    Game game;
    game.Loop();
    lifes = 4;

   }

   }
   //////draw//////
  if(status=="GAME"){
   app->draw(*background);
   scoreboard->draw(*app);

   for(auto i:entities)
     i->draw(*app);
   for(auto i:plifes)
     i->draw(*app);
   app->display();
    }

   if(status=="MENU"){

      app->draw(*background_opt);
      //scoreboard->draw(*app);
      app->draw(*menuRect);
	for (sf::Text text : *menuItems)
			app->draw(text);
      app->display();

   }




  }
}

