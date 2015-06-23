#include "Heatmap.h"

Heatmap::Heatmap()
{
	image = new sf::Image();
	image->create(512, 512, sf::Color::Black);
	lastSaveFilename = "image" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count()) + ".png";
	image->saveToFile(lastSaveFilename);

	start = std::chrono::system_clock::now();
}

Heatmap::~Heatmap()
{
	image->saveToFile(lastSaveFilename);
}

void Heatmap::Update()
{
	
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;

	if (elapsed_seconds.count() >= waitTime)
	{
		for (auto &a : mousePos)
		{
			SetImagePixel(new sf::Vector2i(a.x, a.y), sf::Color(255, 0, 0, 30));
		}

		//image->saveToFile(lastSaveFilename);

		mousePos.clear();
		start = std::chrono::system_clock::now();
	}

}

void Heatmap::SetImagePixel(sf::Vector2i* a, sf::Color color)
{
	SetImagePixel(a->x,		a->y,		color);
										
	SetImagePixel(a->x - 1, a->y,		color);
	SetImagePixel(a->x + 1, a->y,		color);
	SetImagePixel(a->x,	    a->y + 1,	color);
	SetImagePixel(a->x,     a->y - 1,	color);
										
	SetImagePixel(a->x - 2, a->y,		color);
	SetImagePixel(a->x + 2, a->y,		color);
	SetImagePixel(a->x,	    a->y - 2,	color);
	SetImagePixel(a->x,	    a->y + 2,	color);
	SetImagePixel(a->x + 1, a->y + 1,	color);
	SetImagePixel(a->x - 1, a->y + 1,	color);
	SetImagePixel(a->x + 1, a->y - 1,	color);
	SetImagePixel(a->x - 1, a->y - 1,	color);
}

void Heatmap::SetImagePixel(const int x, const int y, sf::Color color)
{
	if (x < 0 || x >= image->getSize().x || y < 0 || y >= image->getSize().y)
		return;

	if (image->getPixel(x, y) != sf::Color::Black)
	{
		//combine colours
		sf::Color combined = image->getPixel(x, y) + color;
		image->setPixel(x, y, combined);
		return;
	}

	image->setPixel(x, y, color);

	return;
}

void Heatmap::SetPos(sf::Vector2i mousePos)
{
	if (mousePos.x > 0 && mousePos.x < 512 && mousePos.y > 0 && mousePos.y < 512)
		this->mousePos.push_back(mousePos);
}