#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#define MAX_NUMBER_OFF_ITEMS 2
using namespace sf;
using namespace std;


class Custom
{
public:
	Custom(float width, float height);
	~Custom();

	void draw(RenderWindow &window);
	//void custom_opt(RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }
	

private:
	int selectedItemIndex;
	Font font;
	Text custom[MAX_NUMBER_OFF_ITEMS];
	Text custom_d, instructions;


};
