#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
public:
	float x, y;
	unsigned int w, h;
	bool clicked = false;
	sf::Texture* texture;
	sf::Sprite* sprite;
public:
	Button(float x, float y, const std::string& fileLocation);
	void Update(sf::RenderWindow* renderWindow);
	void Render(sf::RenderWindow* renderWindow);
};

#endif