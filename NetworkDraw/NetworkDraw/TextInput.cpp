#include "TextInput.h"

TextInput::TextInput(sf::Vector2f& position, sf::Vector2f& size)
{
	TextInput(position, size, "");
}

TextInput::TextInput(sf::Vector2f& position, sf::Vector2f& size, const std::string& defaultText="")
{
	this->pos = new sf::Vector2f(position.x, position.y);
	this->size = new sf::Vector2f(size.x, size.y);
	rect = new sf::RectangleShape(*this->size);
	rect->setPosition(*pos);
	rect->setFillColor(sf::Color::White);
	rect->setOutlineColor(sf::Color::Black);
	rect->setOutlineThickness(1);

	//load font and set text
	font.loadFromFile("Resources/JOKERMAN.TTF");
	string = defaultText;
	this->text = new sf::Text(string, font);
	this->text->setPosition(*pos);
	this->text->setCharacterSize(16);
	this->text->setColor(sf::Color::Black);
}

void TextInput::Update(sf::Event* e, sf::RenderWindow* renderWindow)
{
	//Check for lose focus
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (sf::Mouse::getPosition(*renderWindow).x >= pos->x && sf::Mouse::getPosition(*renderWindow).x <= (pos->x + size->x)
			&& sf::Mouse::getPosition(*renderWindow).y >= pos->y && sf::Mouse::getPosition(*renderWindow).y <= (pos->y + size->y))
		{
			selected = true;
		}
		else
			selected = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && selected)
		selected = false;

	if (selected)
		rect->setFillColor(sf::Color(200, 200, 200, 255));
	else
		rect->setFillColor(sf::Color::White);
}

void TextInput::Input(sf::Event* e)
{
	if (selected)
	{
		if (e->type == sf::Event::KeyPressed)
		{
			std::cout << e->key.code << std::endl;
			if (e->key.code == sf::Keyboard::BackSpace) // delete the last character
			{
				if (string.size() > 0)
				{
					string.pop_back();
					text->setString(string);
				}
			}
		}
		else if (e->type == sf::Event::TextEntered)
		{
			if (e->text.unicode < 128 && e->text.unicode != 8)
			{
				std::cout << e->text.unicode << std::endl;
				string += e->text.unicode;
				text->setString(string);
			}
		}
	}
}

void TextInput::Render(sf::RenderWindow* renderWindow)
{
	renderWindow->draw(*rect);
	renderWindow->draw(*text);
}