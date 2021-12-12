#include "Menu.h"

TitleScreen::TitleScreen()
{
    square721.loadFromFile("images/space age.ttf");
	square721extended.loadFromFile("images/space age.ttf");
	menuRect = new RectangleShape();
	menuRect->setSize(sf::Vector2f(720.0f, 310.0f));
	menuRect->setFillColor(sf::Color(0, 0, 0, 155));
	menuRect->setPosition(440.0f, 380.0f);
	menuItems = new vector<sf::Text>;
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
    menuCursor = 0;
    levelCursor = 0;


}

void TitleScreen::upPressed()
{
	if (--menuCursor < 0)
		menuCursor = 0;
	else
	{
		menuItems[menuCursor + 1].setFillColor(sf::Color::White);
		menuItems[menuCursor].setFillColor(sf::Color::Cyan);
	}
}

short TitleScreen::downPressed()
{
	if (++menuCursor > 2)
		menuCursor = 2;
	else
	{
		menuItems[menuCursor - 1].setFillColor(sf::Color::White);
		menuItems[menuCursor].setFillColor(sf::Color::Cyan);
	}
	return 0;
}

void TitleScreen::rightPressed()
{
	if (menuCursor)
		return;
	if (++levelCursor > 20)
		levelCursor = 20;
	menuItems[0].setString("START : at level " + std::to_string(levelCursor));
}

void TitleScreen::leftPressed()
{
	if (menuCursor)
		return;
	if (--levelCursor < 0)
		levelCursor = 0;
	menuItems[0].setString("START : at level " + std::to_string(levelCursor));
}

short TitleScreen::enterPressed()
{
	return menuCursor;
}

void TitleScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundRect);
	target.draw(menuRect);
	for (sf::Text text : menuItems)
		target.draw(text);
}