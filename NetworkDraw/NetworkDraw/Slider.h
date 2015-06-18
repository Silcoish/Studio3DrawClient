#ifndef SLIDER_H
#define SLIDER_H

#include <iostream>
#include "SFML/Graphics.hpp"

class Slider
{
public:
	float x, y;
	float w, h;
	float min = 0.0f;
	float max = 1.0f;
	float percentage = 0.0f;
	float value = 0.0f;

	sf::RectangleShape rect;
	sf::RectangleShape marker;
public:
	Slider(float x, float y, float w, float h, float min, float max, float startValue);
	void SetColor(sf::Color color);
	void Update(sf::RenderWindow* renderWindow);
	void Render(sf::RenderWindow* renderWindow);
};

#endif