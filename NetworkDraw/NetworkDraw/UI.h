#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "TextInput.h"
#include "Slider.h"

class PreviewColor
{
public:
	sf::RectangleShape* preview;
	void Update(float r, float g, float b) { preview->setFillColor(sf::Color(r * 255, g * 255, b * 255, 255)); }
};

class UI
{
public:
	bool connected = false;

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
	sf::RectangleShape* windowBackgroundRectangle;
	PreviewColor* preview;
public:
	UI(const std::string& ip, const unsigned int port);
	void Update(sf::Event* e, sf::RenderWindow* renderWindow);
	void Render(sf::RenderWindow* renderWindow);
	void Input(sf::Event* e);
};

#endif