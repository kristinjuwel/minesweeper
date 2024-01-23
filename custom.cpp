#include "SFML/Graphics.hpp"
#include "custom.h"
#include <string.h>
#include <iostream>

using namespace sf;
using namespace std;


Custom::Custom(float width, float height)
{
	if (!font.loadFromFile("Pexico.otf"))
	{
		// handle error
	}
    
	//MAX_NUMBER_OFF_ITEMS -> number of text that can be pressed
	//displaying of user interface
	custom[0].setFont(font);				//set up for font
	custom[0].setFillColor(Color::Black);	//set up for font color
	custom[0].setString("PLAY");			//string to be shown
	custom[0].setScale(2.f, 2.f);			//text scale
	custom[0].setPosition(Vector2f(width / 2.5, height / (MAX_NUMBER_OFF_ITEMS + 1) * 2));;		//position of font

	custom[1].setFont(font);				//set up for font
	custom[1].setFillColor(Color::Black);	//set up for font color
	custom[1].setString("QUIT");			//string to be shown
	custom[1].setScale(2.f, 2.f);			//text scale
	custom[1].setPosition(Vector2f(width / 2.5, height / (MAX_NUMBER_OFF_ITEMS + 1) * 2.5));	//position of font

	custom_d.setFont(font);									//set up for font
	custom_d.setFillColor(Color::Black);					//set up for font color
	custom_d.setString("ROWS/COLUMNS/MINES:");				//string to be shown
	custom_d.setScale(2.f, 2.f);							//text scale
	custom_d.setPosition(Vector2f(400, 250)); 				//position of font


	instructions.setFont(font);															//set up for font
	instructions.setFillColor(Color::Black);											//set up for font color
	instructions.setString(" MAX VALUES(30/50*200)\n Input format: 00/00*00");			//string to be shown
	instructions.setPosition(Vector2f(580, 320));										//position of font




	selectedItemIndex = -1;
}
	
Custom::~Custom()
{
} 
void Custom::draw(RenderWindow &window) 	
{	
    /**
	Description:    This function is responsible for displaying the user's input to create
					the custom menu interface.
    Arguments:
        RenderWindow& app	constructing of the window with the use of pointer pointing to app
    Returns:        NONE
    **/
	for (int i = 0; i < MAX_NUMBER_OFF_ITEMS; i++)
	{
		window.draw(custom[i]);
	}
	window.draw(custom_d);
	window.draw(instructions);
}

void Custom::MoveUp() //MoveUp is done using the arrows on the keyboard (move/arrow up)
{
	/**
    Description:    This function is responsible for when the arrow key directed to north (arrow up) is used.
    Arguments:		NONE
    Returns:        NONE	
    **/
	if (selectedItemIndex - 1 >= 0)
	{
		custom[selectedItemIndex].setFillColor(Color::Black);
		selectedItemIndex--;
		custom[selectedItemIndex].setFillColor(Color::Red); //text turns red if selected	
	}
}

void Custom::MoveDown() //MoveDown is done using the arrows on the keyboard (move/arrow down)
{
	/**
    Description:    This function is responsible for when the arrow key directed to south (arrow down) is used.
    Arguments:		NONE
    Returns:        NONE	v//text turns red if selected	
    **/
	if (selectedItemIndex + 1 < MAX_NUMBER_OFF_ITEMS)
	{
		custom[selectedItemIndex].setFillColor(Color::Black);
		selectedItemIndex++;
		custom[selectedItemIndex].setFillColor(Color::Red);
	}
}