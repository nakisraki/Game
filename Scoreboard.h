#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <math.h>
#include <string>
#include "Animation.h"
using namespace sf;
using namespace std;


class Scoreboard
{

  public:
         int level , score;
         float power = 0.5;
         Text t_score;
         string sc = "000";
         Scoreboard(){}

         Scoreboard(Font &f,int lev,int scor)
         {
           level = lev;
           score = scor;
           t_score.setFont(f);
           t_score.setString("Level " + to_string(level) + "  SCORE " + sc + to_string(score));
           t_score.setCharacterSize(35);
           t_score.setFillColor(Color::Magenta);
           t_score.setStyle(Text::Bold);
           t_score.setPosition(655,875);
         }

         void updateScore(int scr ){
            score += scr;
            switch (score)
	        {
	          case 10:
	               sc = "00";
	               break;
	          case 100:
		           sc = "0";
		           break;
	          case 1000:
		      sc = "";
		      break;
	        }
	        if(score==1000 || score==2000 || score==3000 || score==4000 || score == 5000){
	        power+=0.7;
	        level++;
	        }
             t_score.setString("Level " + to_string(level) + "  SCORE " + sc + to_string(score));
         }

         void draw(RenderWindow &app){
             app.draw(t_score);
         }

};

#endif