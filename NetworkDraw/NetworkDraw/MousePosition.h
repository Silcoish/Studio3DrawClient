#ifndef MOUSEPOSITION_H
#define MOUSEPOSITION_H

#include "SFML/Graphics.hpp"

class MousePosition
{
public:
	int x, y;
	char misc;
	sf::RectangleShape* rect;
	sf::Text* text;
public:
	MousePosition() {};
	~MousePosition() { delete rect; };
};

#endif