#pragma once
#include <SFML/Graphics.hpp>

#define MAX_NUMBER_ITEMS 4

class Level
{
public:
	Level(float width, float height);
	~Level();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text level[MAX_NUMBER_ITEMS];

};