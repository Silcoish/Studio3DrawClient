#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "TextInput.h"
#include "Slider.h"

class UI
{
public:
	Button* connectButton;	
	Button* sendRect;
	Button* pixel;
	Button* square;
	Button* line;
	Button* circle;
	Slider* red;
	Slider* green;
	Slider* blue;
	TextInput* ipTextInput;
	TextInput* portTextInput;
	sf::RectangleShape* backgroundRectangle;
public:
	UI(const std::string& ip, const unsigned int port);
	void Update(sf::Event* e, sf::RenderWindow* renderWindow);
	void Render(sf::RenderWindow* renderWindow);
	void Input(sf::Event* e);
};

#endif