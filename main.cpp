#include "SFML/Graphics.hpp"
#include <iostream>
#include "menu.h"
#include "menu.cpp"
#include "level.h"
#include "level.cpp"
#include "mines.cpp"
#include "mines.h"
#include "custom.h"
#include "custom.cpp"
#include <string.h>
using namespace sf;
using namespace std;



int main()
{
	/**
    Description :   This function is where the actual execution of the minesweeper is done. It includes all the functions
					needed coming from the different imported files.
	Arguments:		NONE
    Returns:        NONE
    **/
	if (!font.loadFromFile("Pexico.otf"))
	{
		// handle error
	}
	RenderWindow window(VideoMode(1700, 1000), "MINESWEEPER");				//initialization of window

	Menu menu(window.getSize().x, window.getSize().y);
	Level level(window.getSize().x, window.getSize().y);
	Custom custom(window.getSize().x, window.getSize().y);
	//variable initialization
	int difficulty, pos, pos1;
	String playerInput1, length1, width1, bomb1;
	Text playerText1;


	playerText1.setFont(font);						//set up for font
	playerText1.setFillColor(Color::Red);			//set up for font color
	playerText1.setString("");						//string to be shown
	playerText1.setScale(2.f, 2.f);					//text scale
	playerText1.setPosition(Vector2f(630, 380));	//position of font
	

	while (window.isOpen())     //loop of the display
	{
		Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)			//main menu selection
			{
			case Event::KeyReleased:
				switch (event.key.code)
				{
				case Keyboard::Up:		//keyboard arrow up to navigate the menu
					menu.MoveUp();
					break;

				case Keyboard::Down:	//keyboard arrow down to navigate the menu
					menu.MoveDown();
					break;

				case Keyboard::Return:	//keyboard enter when pressed selects an item in the main menu
					switch (menu.GetPressedItem())
					{
					case 0:					//Choosing to play will reveal the level selection menu
						while (window.isOpen())
						{
							while (window.pollEvent(event))
							{
								switch (event.type)
								{
								case Event::KeyReleased:
									switch (event.key.code)
									{
									case Keyboard::Up:		//keyboard arrow up to navigate the menu
										level.MoveUp();
										break;

									case Keyboard::Down:	//keyboard arrow down to navigate the menu
										level.MoveDown();
										break;

									case Keyboard::Return:	//keyboard enter when pressed selects an item in the level menu
										switch (level.GetPressedItem())
										{
										case 0:			//the player chooses beginner level, the difficulty will be set to 0, and the gameplay function will be called to start the game
											difficulty = 0;
											game_play(window, difficulty, length1, width1, bomb1);
											
											break;
										case 1:			//the player chooses intermediate level, the difficulty will be set to 0, and the gameplay function will be called to start the game
											difficulty = 1;
											game_play(window, difficulty, length1, width1, bomb1);
											break;
										case 2:			//the player chooses expert level, the difficulty will be set to 0, and the gameplay function will be called to start the game
											difficulty = 2;
											game_play(window, difficulty, length1, width1, bomb1);
											break;
										case 3:			//the player chooses custom level, the custom menu will be displayed
											while (window.isOpen())
											{
												while (window.pollEvent(event))
												{
													if (event.type == Event::TextEntered)	//Text input for custom dimensions
													{
														if (event.text.unicode == '\b') // handles backspace explicitly
														{
															if (!playerInput1.isEmpty())
															{
																playerInput1.erase(playerInput1.getSize()- 1, 1);
																playerText1.setString(playerInput1);
															}
														}
														else // all other keypresses
														{
															if((event.text.unicode < 128)&& (playerInput1.getSize()< 9 ) )
															{
																playerInput1 += static_cast<char>(event.text.unicode);
																playerText1.setString(playerInput1);
																
															}

														}
														
													}
													
													switch (event.type)
													{
													case Event::KeyReleased:
														switch (event.key.code)
														{
														case Keyboard::Up:
															custom.MoveUp();
															break;

														case Keyboard::Down:
															custom.MoveDown();
															break;

														case Keyboard::Return:
															switch (custom.GetPressedItem())
															{
															case 0:
																difficulty = 3;
																pos = playerInput1.find("/");
																pos1 = playerInput1.find("*");

																// Copy substring before pos
																length1 = playerInput1.substring(0, pos);
																width1 = playerInput1.substring(pos+1,pos1-3);
																bomb1 = playerInput1.substring(pos1+1);

																game_play(window, difficulty, length1, width1, bomb1);
															
																break;
															case 1:
																window.close();
																break;
															}
															break;
														}
														break;
													case Event::Closed:
														window.close();

														break;

													}
												}
												window.clear(Color::White);
											
												window.draw(playerText1);
					
												custom.draw(window);
												window.display();
											}
											break;
										}

									break;
								}
									break;
								case Event::Closed:
									window.close();
									break;
								}
							}
							window.clear(Color::White);
							level.draw(window);
							window.display();
						}
						break;
					case 1: 				//exit game
                        window.close(); 
						break;
				
					}
					break;
				}
				break;
			case Event::Closed:
				window.close();

				break;
			}
		}
        window.clear(Color::White);
		menu.draw(window);
		window.display();
	}
	return 0;
}