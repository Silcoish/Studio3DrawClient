#include "Slider.h"

Slider::Slider(float x, float y, float w, float h, float min = 0.0f, float max = 1.0f, float startValue = 0.0f)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->min = min;
	this->max = max;
	this->value = startValue;

	rect.setPosition(x, y + 0.25*h);
	rect.setSize(sf::Vector2f(w, h / 2));

	marker.setPosition(x, y);
	marker.setSize(sf::Vector2f(w / 10, h));
	marker.setFillColor(sf::Color::Black);
}

void Slider::SetColor(sf::Color color)
{
	rect.setFillColor(color);
}

void Slider::Update(sf::RenderWindow* renderWindow)
{
	if (sf::Mouse::getPosition(*renderWindow).x >= x && sf::Mouse::getPosition(*renderWindow).x <= (x + w)
		&& sf::Mouse::getPosition(*renderWindow).y >= y && sf::Mouse::getPosition(*renderWindow).y <= (y + h)
		&& sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		percentage = (sf::Mouse::getPosition(*renderWindow).x - x) / w;
		value = (max - min) * percentage;
		marker.setPosition(x + (w * percentage), marker.getPosition().y);
	}
}

void Slider::Render(sf::RenderWindow* renderWindow)
{
	renderWindow->draw(rect);
	renderWindow->draw(marker);
}