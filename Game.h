#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <list>
#include <math.h>
#include "Objects.h"
#include "Animation.h"
#include "Sound.h"
#include "dest.h"
#include "Scoreboard.h"
#include <string>
using namespace sf;
using namespace std;


class graphics
{
  public:
        Texture t1,t2,t3,t4,t5,t6,t7,t8;
        RenderWindow *app;
        Animation *sExplosion;
        Animation *sBullet;
        Animation *sExplosion_ship;
        Animation *sPlayer_go;
        Animation *sRock_small;
        Animation *sRock;
        Animation *sPlayer;
        Animation *sLifes;


        RectangleShape *backgroundRect;
	    string bgmFile;
	    Font square721, square721extended;
	    RectangleShape *menuRect;
	    vector<sf::Text> *menuItems;

};

class Game:public graphics
{


 public:
        string state[10] =  {"MENU", "LOAD", "STAND_BY", "GAME", "GAME_OVER", "PAUSE", "QUIT_GAME", "ENTER_NAME", "OPTIONS", "HIGHSCORE"};


        Sprite *background;
        Sprite *background_opt;
        RenderWindow *app;
        Font font;
        Scoreboard *scoreboard;
        player *p;
        int lifes;
        list<Entity*> plifes;
        list<Entity*> entities;
        bool gamestatus = false;
	Game();
	~Game();
	void Loop();
	void menu();
};


#endif
