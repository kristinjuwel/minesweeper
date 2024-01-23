#pragma once
#include <SFML/Graphics.hpp>

#define SELECTION 2

class Leaderb
{
public:
	Leaderb(float width, float height);
	~Leaderb();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text leaderb[SELECTION];

};

