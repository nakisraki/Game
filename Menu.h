#pragma once
#include "GUI.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
using namespace sf;
class TitleScreen : public GUI
{
	RectangleShape *backgroundRect;
	Sprite *background_opt;
	string bgmFile;
	Font square721, square721extended;
	RectangleShape *menuRect;
	vector<sf::Text> *menuItems;
    short menuCursor;
	short levelCursor;

public:
	TitleScreen();

	void upPressed() override;
	short downPressed() override;
	void leftPressed() override;
	void rightPressed() override;
	short enterPressed() override;

	std::string& getMusic()
	{
		return bgmFile;
	}

	short getLevelCursor()
	{
		return levelCursor;
	}

//private:
//	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};