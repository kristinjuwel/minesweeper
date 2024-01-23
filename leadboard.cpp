#include "SFML/Graphics.hpp"
#include "leadboard.h"
#include <string.h>
#include <iostream>

using namespace sf;
using namespace std;


Leaderb::Leaderb(float width, float height)
{
	if (!font.loadFromFile("Pexico.otf"))
	{
		// handle error
	}
 
	//displaying of user interface
	leaderb[0].setFont(font);				//set up for font
	leaderb[0].setFillColor(Color::Black);	//set up for font color
	leaderb[0].setString("ENTER");			//string to be shown
	leaderb[0].setScale(2.f, 2.f);	
	leaderb[0].setPosition(Vector2f(width / 2.5, height / (SELECTION + 1) * 2));;		//position of font

    leaderb[1].setFont(font);							//set up for font
	leaderb[1].setFillColor(Color::Black);				//set up for font color
	leaderb[1].setString("SEE LEADERBOARD");			//string to be shown
	leaderb[1].setScale(2.f, 2.f);
	leaderb[1].setPosition(Vector2f(width / 3.2, height / (SELECTION + 1) * 2.5));

	selectedItemIndex = -1; 
}
	
Leaderb::~Leaderb()
{
} 


void Leaderb::draw(RenderWindow &window) 	
{	
    /**
	Description:    This function is responsible for displaying the user's input to create
					the buttons leading to the leaderboard interface.
    Arguments:
        RenderWindow& app	constructing of the window with the use of pointer pointing to app
    Returns:        NONE
    **/
	for (int i = 0; i < SELECTION; i++)
	{
		window.draw(leaderb[i]);
	}
}

//choosing of item using the keyboard arrows
//-------------------------------------------
void Leaderb::MoveUp() //MoveUp is done using the arrows on the keyboard (move/arrow up)
{
	/**
    Description:    This function is responsible for when the arrow key directed to north (arrow up) is used.
    Arguments:		NONE
    Returns:        NONE	
    **/
	if (selectedItemIndex - 1 >= 0)
	{
		leaderb[selectedItemIndex].setFillColor(Color::Black);
		selectedItemIndex--;
		leaderb[selectedItemIndex].setFillColor(Color::Red); //text turns red if selected	
	}
}

void Leaderb::MoveDown() //MoveDown is done using the arrows on the keyboard (move/arrow down)
{
	/**
    Description:    This function is responsible for when the arrow key directed to south (arrow down) is used.
    Arguments:		NONE
    Returns:        NONE	v//text turns red if selected	
    **/
	if (selectedItemIndex + 1 < SELECTION)
	{
		leaderb[selectedItemIndex].setFillColor(Color::Black);
		selectedItemIndex++;
		leaderb[selectedItemIndex].setFillColor(Color::Red);
	}
}