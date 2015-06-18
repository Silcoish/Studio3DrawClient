#include "Button.h"

Button::Button(float x, float y, const std::string& fileLocation)
{
	this->x = x;
	this->y = y;
	texture = new sf::Texture();
	texture->loadFromFile(fileLocation);
	sprite = new sf::Sprite();
	sprite->setTexture(*texture);
	sprite->setPosition(x, y);

	w = texture->getSize().x;
	h = texture->getSize().y;
}

void Button::Update(sf::RenderWindow* renderWindow)
{
	if (sf::Mouse::getPosition(*renderWindow).x >= x && sf::Mouse::getPosition(*renderWindow).x <= (x + w)
		&& sf::Mouse::getPosition(*renderWindow).y >= y && sf::Mouse::getPosition(*renderWindow).y <= (y + h)
		&& sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		clicked = true;
	}
	else
		clicked = false;
}

void Button::Render(sf::RenderWindow* renderWindow)
{
	renderWindow->draw((*sprite));
}