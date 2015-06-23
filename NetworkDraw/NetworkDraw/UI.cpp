#include "UI.h"

UI::UI(const std::string& ip, const unsigned int port)
{
	connectButton = new Button(562, 120, "Resources/Button.png");
	sendRect = new Button(562, 170, "Resources/Button2.png");

	pixel = new Button(525, 220, "Resources/ButtonPixel.png");
	square = new Button(625, 220, "Resources/ButtonSquare.png");
	circle = new Button(525, 300, "Resources/ButtonCircle.png");
	line = new Button(625, 300, "Resources/ButtonLine.png");

	red = new Slider(525, 400, 100, 30, 0.0f, 1.0f, 0.0f);
	red->SetColor(sf::Color::Red);

	green = new Slider(525, 440, 100, 30, 0.0f, 1.0f, 0.0f);
	green->SetColor(sf::Color::Green);

	blue = new Slider(525, 480, 100, 30, 0.0f, 1.0f, 0.0f);
	blue->SetColor(sf::Color::Blue);

	ipTextInput = new TextInput(sf::Vector2f(562, 10), sf::Vector2f(100, 30), /*"127.0.0.1"*/"10.40.61.0"/*"10.40.60.35"*/);
	portTextInput = new TextInput(sf::Vector2f(562, 70), sf::Vector2f(100, 30), "1300");
	backgroundRectangle = new sf::RectangleShape();
	backgroundRectangle->setSize(sf::Vector2f(200, 512));
	backgroundRectangle->setOutlineColor(sf::Color::Red);
	backgroundRectangle->setOutlineThickness(1);
	backgroundRectangle->setPosition(512, 0);
}

void UI::Update(sf::Event* e, sf::RenderWindow* renderWindow)
{
	connectButton->Update(renderWindow);
	sendRect->Update(renderWindow);

	pixel->Update(renderWindow);
	circle->Update(renderWindow);
	line->Update(renderWindow);
	square->Update(renderWindow);

	red->Update(renderWindow);
	green->Update(renderWindow);
	blue->Update(renderWindow);

	ipTextInput->Update(e, renderWindow);
	portTextInput->Update(e, renderWindow);
}

void UI::Render(sf::RenderWindow* renderWindow)
{
	renderWindow->draw(*backgroundRectangle);
	connectButton->Render(renderWindow);
	sendRect->Render(renderWindow);

	pixel->Render(renderWindow);
	circle->Render(renderWindow);
	line->Render(renderWindow);
	square->Render(renderWindow);

	red->Render(renderWindow);
	green->Render(renderWindow);
	blue->Render(renderWindow);

	ipTextInput->Render(renderWindow);
	portTextInput->Render(renderWindow);
}

void UI::Input(sf::Event* e)
{
	ipTextInput->Input(e);
	portTextInput->Input(e);
}
