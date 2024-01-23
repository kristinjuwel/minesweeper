#include "level.h"

using namespace sf;


Level::Level(float width, float height)
{
	if (!font.loadFromFile("Pexico.otf"))
	{
		// handle error
	}
    

	//displaying of user interface
	level[0].setFont(font);					//set up for font
	level[0].setFillColor(Color::Black);	//set up for font color
	level[0].setString("BEGINNER");			//string to be shown
	level[0].setScale(2.f, 2.f);
	level[0].setPosition(Vector2f(width / 2.7, height / (MAX_NUMBER_ITEMS + 1) * 1));	//position of font

	level[1].setFont(font);					//set up for font
	level[1].setFillColor(Color::Black);	//set up for font color
	level[1].setString("INTERMEDIATE");		//string to be shown
	level[1].setScale(2.f, 2.f);
	level[1].setPosition(Vector2f(width / 2.9, height / (MAX_NUMBER_ITEMS + 1) * 2)); 	//position of font

	level[2].setFont(font);					//set up for font
	level[2].setFillColor(Color::Black);	//set up for font color
	level[2].setString("EXPERT");			//string to be shown
	level[2].setScale(2.f, 2.f);
	level[2].setPosition(Vector2f(width / 2.5, height / (MAX_NUMBER_ITEMS + 1) * 3));	//position of font

    level[3].setFont(font);					//set up for font
	level[3].setFillColor(Color::Black);	//set up for font color
	level[3].setString("CUSTOM");			//string to be shown
	level[3].setScale(2.f, 2.f);
	level[3].setPosition(Vector2f(width / 2.55, height / (MAX_NUMBER_ITEMS + 1) * 4));	//position of font


	selectedItemIndex = -1;
}


Level::~Level()
{
}

void Level::draw(RenderWindow &window)
{
	/**
    Description:    This function is responsible for displaying the level screen on the window.
    Arguments:
        RenderWindow& app	constructing of the window with the use of pointer pointing to app
    Returns:        NONE
    **/
	for (int i = 0; i < MAX_NUMBER_ITEMS; i++)
	{
		window.draw(level[i]);
	}
}

//choosing of level using the keyboard arrows
//-------------------------------------------
void Level::MoveUp() 
{
	/**
    Description:    This function is responsible for when the arrow key directed to north (arrow up) is used.
    Arguments:		NONE
    Returns:        NONE
    **/
	if (selectedItemIndex - 1 >= 0)
	{
		level[selectedItemIndex].setFillColor(Color::Black);
		selectedItemIndex--;
		level[selectedItemIndex].setFillColor(Color::Red);		//text turns red if selected
	}
}

void Level::MoveDown() 
{
	/**
    Description:    This function is responsible for when the arrow key directed to south (arrow down) is used.
    Arguments:		NONE
    Returns:        NONE
    **/
	if (selectedItemIndex + 1 < MAX_NUMBER_ITEMS)
	{
		level[selectedItemIndex].setFillColor(Color::Black);
		selectedItemIndex++;
		level[selectedItemIndex].setFillColor(Color::Red);		//text turns red if selected
	}
}