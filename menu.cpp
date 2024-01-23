#include "menu.h"

using namespace sf;


Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("Pexico.otf"))
	{
		// handle error
	}

	//MAX_NUMBER_OFF_ITEMS -> number of text that can be pressed
	//displaying of user interface
	menu[0].setFont(font);					//set up for font
	menu[0].setFillColor(Color::Black);		//set up for font color
	menu[0].setString("PLAY");				//string to be shown
	menu[0].setScale(3.f, 3.f);
	menu[0].setPosition(Vector2f(width / 2.3, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));	//position of font

	menu[1].setFont(font);					//set up for font
	menu[1].setFillColor(Color::Black);		//set up for font color
	menu[1].setString("QUIT");			//string to be shown
	menu[1].setScale(3.f, 3.f);
	menu[1].setPosition(Vector2f(width / 2.3, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));	//position of font


	selectedItemIndex = -1;
}


Menu::~Menu()
{
}

void Menu::draw(RenderWindow &window)
{
	/**
    Description:    This function is responsible for displaying the menu screen on the window.
    Arguments:
        RenderWindow& app	constructing of the window with the use of pointer pointing to app
    Returns:        NONE
    **/
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}
//choosing of item using the keyboard arrows
//-------------------------------------------
void Menu::MoveUp()
{
	/**
    Description:    This function is responsible for when the arrow key directed to north (arrow up) is used.
    Arguments:		NONE
    Returns:        NONE
    **/
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(Color::Black);	
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(Color::Red);	//text turns red if selected
	}
}

void Menu::MoveDown()
{
	/**
    Description:    This function is responsible for when the arrow key directed to south (arrow down) is used.
    Arguments:		NONE
    Returns:        NONE
    **/
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(Color::Black);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(Color::Red);	//text turns red if selected
	}
}