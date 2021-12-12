#ifndef SOUND_H
#define SOUND_H
#include <SFML/Audio.hpp>
#include <string>
using namespace sf;
class Sounds
{
  public:
      std::vector<std::string> s = {"sound/crash.wav","sound/expl.wav","sound/shoot.ogg"};
      SoundBuffer bulletBuffer;
	  SoundBuffer explBuffer;
	  SoundBuffer crashBuffer;
	  Sound bullet;
	  Sound expl;
	  Sound crash;
	  
	  Sounds(){
	  
	    bulletBuffer.loadFromFile(s[2]);
        explBuffer.loadFromFile(s[1]);
        crashBuffer.loadFromFile(s[0]);
        bullet.setBuffer(bulletBuffer);
        expl.setBuffer(explBuffer);
         crash.setBuffer(crashBuffer);
	  }



};

#endif
