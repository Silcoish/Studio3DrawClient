#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include <iostream>
#include "SFML/Graphics.hpp"

class TextInput
{
private:
	bool selected = false;
	sf::Color startColor;
	sf::Vector2f* pos;
	sf::Vector2f* size;
	sf::RectangleShape* rect;
public:
	std::string string;
	sf::Font font;
	sf::Text* text;
public:
	TextInput(sf::Vector2f& position, sf::Vector2f& size);
	TextInput(sf::Vector2f& position, sf::Vector2f& size, const std::string& defaultText);
	void Update(sf::Event* e, sf::RenderWindow* renderWindow);
	void Input(sf::Event* e);
	void Render(sf::RenderWindow* renderWindow);

	//Getters
	//Need to implement them still
	
};

#endif