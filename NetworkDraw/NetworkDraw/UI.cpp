#include "UI.h"

UI::UI(const std::string& ip, const unsigned int port)
{
	connectButton = new Button(200, 570, "Resources/Button.png");

	sendRect = new Button(190, 530, "Resources/Button2.png");

	pixel = new Button(10, 530, "Resources/ButtonPixel.png");
	square = new Button(100, 530, "Resources/ButtonSquare.png");
	circle = new Button(525, 300, "Resources/ButtonCircle.png");
	line = new Button(625, 300, "Resources/ButtonLine.png");

	red = new Slider(380, 515, 100, 30, 0.0f, 1.0f, 0.0f);
	red->SetColor(sf::Color::Red);

	green = new Slider(380, 547, 100, 30, 0.0f, 1.0f, 0.0f);
	green->SetColor(sf::Color::Green);

	blue = new Slider(380, 579, 100, 30, 0.0f, 1.0f, 0.0f);
	blue->SetColor(sf::Color::Blue);

	preview = new PreviewColor();
	preview->preview = new sf::RectangleShape();
	preview->preview->setSize(sf::Vector2f(50, 94));
	preview->preview->setPosition(sf::Vector2f(320, 515));

	ipTextInput = new TextInput(sf::Vector2f(10, 520), sf::Vector2f(150, 30), "127.0.0.1"/*"10.40.61.0"/*"10.40.60.35"*/);
	portTextInput = new TextInput(sf::Vector2f(10, 570), sf::Vector2f(150, 30), "1300");

	backgroundRectangle = new sf::RectangleShape();
	backgroundRectangle->setSize(sf::Vector2f(512, 100));
	backgroundRectangle->setOutlineColor(sf::Color::White);
	backgroundRectangle->setOutlineThickness(1);
	backgroundRectangle->setPosition(0, 512);
	windowBackgroundRectangle = new sf::RectangleShape();
	windowBackgroundRectangle->setScale(sf::Vector2f(800, 800));
	windowBackgroundRectangle->setFillColor(sf::Color::White);
}

void UI::Update(sf::Event* e, sf::RenderWindow* renderWindow)
{
	if (!connected)
	{
		connectButton->Update(renderWindow);
		ipTextInput->Update(e, renderWindow);
		portTextInput->Update(e, renderWindow);
	}
	else
	{
		sendRect->Update(renderWindow); 

		pixel->Update(renderWindow);
		circle->Update(renderWindow);
		line->Update(renderWindow);
		square->Update(renderWindow);

		red->Update(renderWindow);
		green->Update(renderWindow);
		blue->Update(renderWindow);

		preview->Update(red->value, green->value, blue->value);
	}
}

void UI::Render(sf::RenderWindow* renderWindow)
{
	renderWindow->draw(*windowBackgroundRectangle);
	renderWindow->draw(*backgroundRectangle);
	
	if (!connected)
	{
		connectButton->Render(renderWindow);
		ipTextInput->Render(renderWindow);
		portTextInput->Render(renderWindow);
	}
	else
	{
		sendRect->Render(renderWindow);

		pixel->Render(renderWindow);
		circle->Render(renderWindow);
		line->Render(renderWindow);
		square->Render(renderWindow);

		red->Render(renderWindow);
		green->Render(renderWindow);
		blue->Render(renderWindow);

		renderWindow->draw(*preview->preview);
	}

}

void UI::Input(sf::Event* e)
{
	ipTextInput->Input(e);
	portTextInput->Input(e);
}
