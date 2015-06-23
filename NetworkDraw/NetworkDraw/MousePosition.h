#ifndef MOUSEPOSITION_H
#define MOUSEPOSITION_H

#include "SFML/Graphics.hpp"

class MousePosition
{
public:
	int x, y;
	char misc;
	unsigned int miscInt;
	sf::Sprite* mouseImage;
	sf::Font font;
	sf::Text* text;
public:
	MousePosition() {};
	~MousePosition() { delete mouseImage; };
};

#endif