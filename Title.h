#ifndef TITLE_H
#define TITLE_H

class TitleScreen : public GUI
{
	RectangleShape *backgroundRect;
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

//	std::string& getMusic()
//	{
//		return bgmFile;
//	}

	short getLevelCursor()
	{
		return levelCursor;
	}


#endif
