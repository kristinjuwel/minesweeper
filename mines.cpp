#include <SFML/Graphics.hpp>
#include "mines.h"
#include "leadboard.h"
#include "leadboard.cpp"
#include <bits/stdc++.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <fstream>
//set to 50 to avoid spilling to the next line
#define MAX_COLUMN 50   
#define MAX_ROW 50      

using namespace sf;
using namespace std;

int i, j;
int board_col, board_row, board_bombs, time_spent;
int gameTime = 0;
int w = 32; // image pixel length
int board[MAX_COLUMN+1][MAX_ROW+1];
int user_board[MAX_COLUMN+1][MAX_ROW+1]; // for showing
int firstMove, bombs_found=0;
string game_File;


Font font;
Text gameTimer, l_board1,l_board2,l_board3, l_board4, l_board5;


void UpdateLeaderboard(int time_spent, string playerInput)
{
    /**
    Description :   It updates the values in the leaderboard text file.
    Arguments:
        int time_spent   	elapsed time the player took to finish the game
		string playerInput	name of the player/user inputted
    Returns:        NONE
    **/

    //open appropriate leaderboard file to extract values
    int time1, time2, time3, time4, time5;
    string name1, name2, name3, name4, name5;
    string sLine;

    //extract values and assign to appropriate variables
    ifstream fsInput(game_File);
    getline(fsInput, sLine);
    fsInput >> time1 >> name1;
    getline(fsInput, sLine);
    fsInput >> time2 >> name2;
    getline(fsInput, sLine);
    fsInput >> time3 >> name3;
    getline(fsInput, sLine);
    fsInput >> time4 >> name4;
    getline(fsInput, sLine);
    fsInput >> time5 >> name5;

    //compare current score to the determine the order in the leaderboard
    if(time_spent <= time1 || time1 == 0)  //score is 1st place
    {
        //shift other scores down
        time5 = time4;
        name5 = name4;
        time4 = time3;
        name4 = name3;
        time3 = time2;
        name3 = name2;
        time2 = time1;
        name2 = name1;
        time1 = time_spent;
        name1 = playerInput;

    }else if((time_spent <= time2  || time2 == 0) && time_spent > time1)
    {
        time5 = time4;
        name5 = name4;
        time4 = time3;
        name4 = name3;
        time3 = time2;
        name3 = name2;
        time2 = time_spent;
        name2 = playerInput;

    }else if((time_spent <= time3 || time3 == 0) && time_spent > time2)
    {
        time5 = time4;
        name5 = name4;
        time4 = time3;
        name4 = name3;
        time3 = time_spent;
        name3 = playerInput;

    }else if((time_spent <= time4 || time4 == 0) && time_spent > time3)
    {
        time5 = time4;
        name5 = name4;
        time4 = time_spent;
        name4 = playerInput;

    }else if((time_spent <= time5 || time5 == 0) && time_spent > time4)
    {
        time5 = time_spent;
        name5 = playerInput;

    }
    fsInput.close();
    
	ofstream fsOutput(game_File);
	fsOutput << "Leaderboard" << "\n";
    fsOutput << time1 << " " << name1 << "\n";
    fsOutput << time2 << " " << name2 << "\n";
    fsOutput << time3 << " " << name3 << "\n";
    fsOutput << time4 << " " << name4 << "\n";
    fsOutput << time5 << " " << name5 << "\n";
    fsOutput.close();

}

bool new_highscore(int time_spent, int difficulty)
{
    /**
    Description:	Checks if the current score belongs to the leaderboard.
    Arguments:
        int time_spent   elapsed time the player took to finish the game
        int difficulty   difficulty level chosen by the player
	Returns:        
		true		new score is at least in 5th place
		false		new score is not at least in 5th place	
    **/

    //determine the leaderboard file to be loaded using difficulty
    if (difficulty == 0)
        game_File = "score_beginner.txt";
    else if (difficulty == 1)
        game_File = "score_intermediate.txt";
    else if (difficulty == 2)
        game_File = "score_expert.txt";

    //open file to check if the current score is
    ifstream fsInput(game_File);
    int time5, iLine = 1;
    string name5, sLine; //name5 - dummy variable for name column

    while (getline(fsInput, sLine))
    {
        if (iLine == 5)
        {
            fsInput >> time5 >> name5;
        }
        iLine++;
    }

    if (time_spent > time5 && time5 != 0)
        return false;
    else if (time_spent < time5 || time5 == 0) //new score is at least in the 5th place
        return true;
	fsInput.close();	
	return true;

}	

void make_board(int board_col, int board_row)
{
	/**
    Description:    This function creates the game board according to the total numbers of rows and columns which are both
                    dependable on the chosen level of difficulty. Each cell will be filled with 10 (being the image of the
					closed cell).
    Arguments:
        int board_col 	total number of columns based on the chosen difficulty
		int board_row 	total number of rows based on the chosen difficulty
    Returns:        NONE
    **/
	for(int i=1; i<=board_col; i++)
	{
		for (int j = 1; j <= board_row; j++)
		{
			user_board[i][j] = 10;	//image 10 will be placed on each cell (image 10 -> closed cell)
		}
	}
}
		
void make_bomb(int board_col, int board_row, int board_bombs, int a, int b) 
{
	/**
	Description:    This function is to used to generate bombs in random cells in the game. The bomb (image) corresponds to 9.
	Arguments:		
		int board_col 	total number of columns based on the chosen difficulty
		int board_row 	total number of rows based on the chosen difficulty
		int board_bombs		number of bombs on the board based on the chosen difficulty
		int a				column coordinate of first move
		int b				row coordinate of first move
	Returns:		NONE   
	**/
	int count = 0;
    while (count < board_bombs) {
        int x = rand() % board_col+1;
		int y = rand() % board_row+1;
        if (board[x][y] != 9 && board[x][y] != -2) {
            board[x][y] = 9;
            ++count;
        }
    }
	if (board[a][b] == -2)
        board[a][b] = 0;
}

void cell_number(int board_col, int board_row)
{
	/**
    Description:    This function will generate the number of bombs in the 8 adjacent tiles if the cell chosen by the user
					does not contain a bomb.
    Arguments:		
		int board_col 	total number of columns based on the chosen difficulty
		int board_row 	total number of rows based on the chosen difficulty
    Returns:        NONE
    **/
	for (int i = 1; i <= board_col; i++)
	{
		for (int j = 1; j <= board_row; j++)
		{
			if (board[i][j] != 9)
			{
				int b_bombs = 0;
				if (board[i - 1][j - 1] == 9)	//checking northwest cell
				{
					b_bombs++;					//increment for b_bombs (b_bombs -> indicating how many bombs)
				}
				if (board[i - 1][j] == 9)		//checking west cell
				{
					b_bombs++;
				}
				if (board[i-1][j+1] == 9)		//checking southwest cell 
				{
					b_bombs++;
				}
				if (board[i][j - 1] == 9)		//checking north cell
				{
					b_bombs++;
				}
				if (board[i][j + 1] == 9)		//checking south cell 
				{
					b_bombs++;
				}
				if (board[i + 1][j - 1] == 9)	//checking northeast cell 
				{
					b_bombs++;
				}
				if (board[i + 1][j] == 9)		//checking east cell 
				{
					b_bombs++;
				}
				if (board[i + 1][j + 1] == 9)	//checking southeast cell
				{
					b_bombs++;
				}
				board[i][j] = b_bombs;			//generating a number and putting it in the cell
												//(based on how many bombs are in adjacent tiles)
			}
		}
	}
}

void reveal_cell(int i, int j)
{
    /**
    Description:   	A recursive function that reveals the adjacent safe (empty) cells from the 8 directions that is
					bounded by cells with numbers in the board (user_board).
    Arguments:
        int i    	column component of the cell address
        int j    	row component of the cell address
    Returns:        NONE
    **/

    if (user_board[i][j] == 10 && board[i][j] != 9)
    {
        user_board[i][j] = board[i][j];

        //recursive procedure to reveal safe tiles -> (blanks and digits)
        if (board[i][j] == 0)
        {
			reveal_cell(i-1, j);   	 //west cell
            reveal_cell(i+1, j);   	 //east cell
            reveal_cell(i, j-1);   	 //north cell
            reveal_cell(i, j+1);   	 //south cell
            reveal_cell(i-1, j-1);   //northwest cell
            reveal_cell(i+1, j-1);   //northeast cell
            reveal_cell(i+1, j+1);   //southeast cell
            reveal_cell(i-1, j+1);   //southwest cell
        }
    }
}

bool check_win(int bombs_found, int board_bombs)
{
	/**
    Description:    This function will return true if the bombs_found (a.k.a the bombs properly flagged) is the same number
					as the specified number of bombs per difficulty.
    Arguments:
        int bombs_found   	number of bombs found by the user
		int board_bombs		number of bombs on the board based on the chosen difficulty
    Returns:        
		true		The bombs_found is the same number as the specified number of bombs per difficulty.
		false		The bombs_found is not the same number as the specified number of bombs per difficulty.
    **/
    if (bombs_found == board_bombs)
        return true;
    else
        return false;

}

bool game_over(int i, int j)
{
	/**
    Description:    This function will return true if the bombs_found (a.k.a the bombs properly flagged) is the same number
					as the specified number of bombs per difficulty.
    Arguments:
        int i	   	column coordinate from user input
        int j	   	row coordinate from user input
    Returns:        
		true		The cell chosen by the user has a bomb
		false		The cell chosen by the user does not have a bomb
    **/
	if(board[i][j] == 9)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void display_leadb(RenderWindow& window, int difficulty)
{
	/**
    Description:    The implementation of the leaderboard window.
    Arguments:
        RenderWindow& window	constructing of the window with the use of pointer pointing to app
		int difficulty			level selected
    Returns:        NONE
    **/
	Text leadr("Leaderboard",font,75);
    leadr.setPosition(Vector2f(window.getSize().x/3, window.getSize().y/7));
    leadr.setFillColor(Color::Magenta);
	
	if (difficulty == 0)
	{
		game_File = "score_beginner.txt";
	}
	else if (difficulty == 1)
	{
		game_File = "score_intermediate.txt";
	}
	else if (difficulty == 2)
	{
		game_File = "score_expert.txt";
	}
	ifstream in(game_File);
	int time;
	ostringstream top1, top2, top3, top4, top5;
	string name_1, name_2, name_3, name_4, name_5, name;
	int time_1, time_2, time_3, time_4, time_5;
	
	string line;

	getline(in, line);
	in >> time_1 >> name_1;
	
	getline(in,line);
	in >> time_2 >> name_2;

	getline(in,line);
	in >> time_3 >> name_3;
	
	getline(in,line);
	in >> time_4 >> name_4;

	getline(in,line);
	in >> time_5 >> name_5;



	top1 << "1st: " + name_1 + "   Time in seconds: " + to_string(time_1);
	top2 << "2nd: " + name_2 + "   Time in seconds: " + to_string(time_2);
	top3 << "3rd: " + name_3 + "   Time in seconds: " + to_string(time_3);
	top4 << "4th: " + name_4 + "   Time in seconds: " + to_string(time_4);
	top5 << "5th: " + name_5 + "   Time in seconds: " + to_string(time_5);
	
	l_board1.setFont(font);
	l_board1.setFillColor(Color::Black);
	l_board1.setCharacterSize(65);
	l_board1.setPosition(Vector2f(200,300));
	l_board1.setString(top1.str());
	l_board2.setFont(font);
	l_board2.setFillColor(Color::Black);
	l_board2.setCharacterSize(65);
	l_board2.setPosition(Vector2f(200, 400));
	l_board2.setString(top2.str());
	l_board3.setFont(font);
	l_board3.setFillColor(Color::Black);
	l_board3.setCharacterSize(65);
	l_board3.setPosition(Vector2f(200, 500));
	l_board3.setString(top3.str());
	l_board4.setFont(font);
	l_board4.setFillColor(Color::Black);
	l_board4.setCharacterSize(65);
	l_board4.setPosition(Vector2f(200,600));
	l_board4.setString(top4.str());
	l_board5.setFont(font);
	l_board5.setFillColor(Color::Black);
	l_board5.setCharacterSize(65);
	l_board5.setPosition(Vector2f(200, 700));
	l_board5.setString(top5.str());

	Event e;
	while (window.isOpen())                  //game loop(as long as the window is open)
	{
		while (window.pollEvent(e))
		{	
			if (e.type == Event::Closed)     //if the exit button is clicked,
			{
				window.close();              //window closes
			}
				
		}
		window.clear(Color::White);
		window.draw(leadr);
		window.draw(l_board1);
		window.draw(l_board2);
		window.draw(l_board3);
		window.draw(l_board4);
		window.draw(l_board5);
		window.display();
		
	}
}


void game_play(RenderWindow& app, int difficulty, string length1, string width1, string bomb1)
{
	app.setFramerateLimit(60);
	/**
    Description:    The implementation of the actual game.
    Arguments:
        RenderWindow& app	constructing of the window with the use of pointer pointing to app
		int difficulty	   	chosen level of the user
		string length1		string responsible for the custom length (columns)
		string width1		string responsible for the custom width (rows)
		string bomb1		string responsible for the custom number of mines
    Returns:        NONE
    **/
   	Leaderb leaderb(app.getSize().x, app.getSize().y);
	//BEGINNER
	if (difficulty==0)
	{
		board_col = 9;
		board_row = 9;
		board_bombs = 10;
	}
	//INTERMEDIATE
	else if (difficulty==1)
	{
		board_col = 16;
		board_row = 16;
		board_bombs = 40;
	}
	//EXPERT
	else if (difficulty==2)
	{
		board_col = 30;
		board_row = 16;
		board_bombs = 99;
	}
	//CUSTOM
	else if (difficulty ==3)
	{
		board_col = stoi(width1);
		board_row = stoi(length1);
		board_bombs = stoi(bomb1);
	}
	
	if (!font.loadFromFile("Pexico.otf"))
	{

	}
	gameTimer.setFont(font);
	gameTimer.setFillColor(Color::Red);
	gameTimer.setCharacterSize(50);
	gameTimer.setScale(2.f, 2.f);
	gameTimer.setPosition(Vector2f(1500,50));
    String playerInput, player_input;
    Text playerText("",font,60);
    playerText.setPosition(Vector2f(app.getSize().x/2.5, app.getSize().y/2));;
    playerText.setFillColor(Color::Magenta);
	Text congrats("    You won the game!\n Please enter your name:",font,60);
    congrats.setPosition(Vector2f(app.getSize().x/5, app.getSize().y/4));
    congrats.setFillColor(Color::Black);
	Text congrattime1("You won the game!\n Thanks for playing!",font,75);
    congrattime1.setPosition(Vector2f(app.getSize().x/5, app.getSize().y/5));
    congrattime1.setFillColor(Color::Black);
	
	

	srand(time(0)); 		//the random function using the time in seconds since the Unix epoch as a new seed
    Clock clock;			//used to know the duration of the game
    Time timer, timer2; 

    Texture t;                                      //makes a texture t for the tiles
	t.loadFromFile("images/tiles.jpg");             //loads the image to be used for the tiles
	Sprite s(t);                                    //sets the tiles as sprite

	make_board(board_col, board_row);     			//initializes the game board

	while (app.isOpen())                            //game loop(as long as the window is open)
	{
		Vector2i pos = Mouse::getPosition(app);     //takes the position of the mouse
		int x = pos.x / w;                                   
		int y = pos.y / w;
		Event e;                                    //assigns event to variable e

		timer = clock.getElapsedTime();
		if (timer.asSeconds() > gameTime)
			gameTime++;
			
		while (app.pollEvent(e))
		{
						switch (e.type)
			{
				case Event::KeyReleased:
					switch (e.key.code)
					{
					case Keyboard::Up:
						leaderb.MoveUp();
						break;

					case Keyboard::Down:
						leaderb.MoveDown();
						break;

					case Keyboard::Return:
						switch (leaderb.GetPressedItem())
						{
						case 0:
							time_spent = gameTime;
							if (difficulty != 3)
							{
								if(new_highscore(time_spent, difficulty))
								{
									//update leaderboard file
									UpdateLeaderboard(time_spent, playerInput);
									
								}
							}
							break;
						
						case 1:
							display_leadb(app, difficulty);
							break;
							
						}
						break;
					}
					break;
				case Event::Closed:
					app.close();

					break;
			}
			
			if (e.type == Event::Closed)     //if the exit button is clicked,
			{
				app.close();                 //window closes
			}				
			if (e.type == Event::MouseButtonPressed)        //tracks the actions done using mouse
			{
				if (e.mouseButton.button == Mouse::Left)    //if the left mouse button is clicked,
				{
					
					if (firstMove == 0)
					{
						make_bomb(board_col, board_row, board_bombs, x, y);
						cell_number(board_col, board_row);
						reveal_cell(x,y);
						firstMove = 1;	
					}

					if (board[x][y] == 0)
					{
						reveal_cell(x,y);
					}
					else
					{
						user_board[x][y] = board[x][y];
					}
				}
				else if (e.mouseButton.button == Mouse::Right)  //If you flag a cell:
				{
					if (user_board[x][y] == 11)
					{
						user_board[x][y] = 10;
					}
					else if (user_board[x][y] > 9)
					{
						user_board[x][y] = 11;
					}
					if (board[x][y] == 9) 	//If the cell contains a bomb
					{
						bombs_found++; 		//Add 1 to the number of bombs flagged correctly
					}
				}	
				
			}
			if (e.type == Event::TextEntered)
			{
				if (e.text.unicode == '\b') //handles backspace explicitly
				{
					if (!playerInput.isEmpty())
					{
						playerInput.erase(playerInput.getSize()- 1, 1);
						playerText.setString(playerInput);
					}
				}
				else //all other keypresses
				{
					if((e.text.unicode < 128)&& (playerInput.getSize()< 6 ) )
					{
						playerInput += static_cast<char>(e.text.unicode);
						playerText.setString(playerInput);
						
					}
					
				}
				
			}

		}
		app.clear(Color::White);
		
        if (check_win(bombs_found, board_bombs)== true)
		{
			ostringstream timespent;
			timespent << gameTime;
			clock.restart();
			int time_spent = gameTime;
			app.clear(Color::White);
			if (difficulty != 3)
			{
				app.draw(congrats);
				app.draw(playerText);
				leaderb.draw(app);
			}
			else if (difficulty == 3)
			{
				app.draw(congrattime1);
			}
			app.display();
			
		}
		else
		{
			for (int i = 1; i <= board_col; i++)
			{
				for (int j = 1; j <= board_row; j++)
				{
					if (user_board[x][y] == 9)
					{
						user_board[i][j] = board[i][j];
						clock.restart();
					}
					s.setTextureRect(IntRect(user_board[i][j] * w, 0, w, w));
					s.setPosition(i * w, j * w);
								
					app.draw(s);
				
				}
			}
			
			//responsible for the timer
			ostringstream timespent;
			timespent << gameTime;
			gameTimer.setString(timespent.str());
			app.draw(gameTimer);
			app.display();
		}
    }
}

