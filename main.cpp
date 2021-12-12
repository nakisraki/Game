#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <list>
#include <math.h>
#include "Objects.h"
#include "Animation.h"
#include "Sound.h"
#include "dest.h"
#include "Game.h"
#include "Game.cpp"
#include "GUI.h"
#include <string>
using namespace sf;
using namespace std;




int main()
{
   

    Game game;
    game.Loop();

    return 0;
}
