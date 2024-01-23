#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#define MAX_COLUMN 50   //set to 50 to avoid spilling to the next line
#define MAX_ROW 50      //

using namespace sf;
using namespace std;

void UpdateLeaderboard(int, string);
bool new_highscore(int , int );
void make_board(int, int);
void make_bomb(int, int, int, int, int);
void cell_number(int, int);
bool check_win(int, int);
bool game_over(int, int);
void display_leadb(RenderWindow&, int);
void game_play(RenderWindow&, int, string, string, string);
