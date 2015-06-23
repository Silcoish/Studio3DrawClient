#include <iostream>
#include <SFML/Graphics.hpp>
#include "UI.h"
#include "Packet.h"
#include "NetworkConnection.h"
#include "Heatmap.h"

const float targetTime = 1.0f/60.0f;

void main()
{
	srand(time(0));

	char* ip = "127.0.0.1";
	unsigned int port = 1300;

	enum drawType
	{
		PIXEL,
		LINE,
		CIRCLE,
		SQUARE
	};

	drawType type = PIXEL;

	sf::RenderWindow window(sf::VideoMode(712, 512), "SFML Network Drawing Program");
	UI ui(ip, port);
	Heatmap heatmap;
	NetworkConnection connection(&heatmap);

	//set up deltaT variables
	std::chrono::high_resolution_clock::time_point lastTime = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point curTime  = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> deltaT = std::chrono::duration_cast<std::chrono::duration<double>>(curTime - lastTime);

	while (window.isOpen())
	{
		//deltaT calculations
		curTime = std::chrono::high_resolution_clock::now();
		deltaT = std::chrono::duration_cast<std::chrono::duration<double>>(curTime - lastTime);

		if (deltaT.count() >= targetTime)
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				ui.Input(&event);
			}

			if (ui.connectButton->clicked)
			{
				if (!connection.connected)
				{
					std::cout << "Connecting" << std::endl;
					const char* i = ui.ipTextInput->string.c_str();
					int p = atoi(ui.portTextInput->string.c_str());
					connection.Connect(i, p);
					std::cout << "Result: " << connection.connected << std::endl;
					connection.ui = &ui;
				}
			}

			if (ui.pixel->clicked)
			{
				type = PIXEL;
			}
			else if (ui.line->clicked)
			{
				type = LINE;
			}
			else if (ui.circle->clicked)
			{
				type = CIRCLE;
			}
			else if (ui.square->clicked)
			{
				type = SQUARE;
			}

			if (ui.sendRect->clicked)
			{
				ui.sendRect->clicked = false;
				connection.ClearScreen();
				
			}

			if (connection.connected)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(window).x >= 0 && sf::Mouse::getPosition(window).x <= 512 && sf::Mouse::getPosition(window).y >= 0 && sf::Mouse::getPosition(window).y <= 512)
				{
					switch (type)
					{
					case PIXEL:
					{
						PacketPixel* pixel = new PacketPixel();
						pixel->type = Packet::e_pixel;
						pixel->x = sf::Mouse::getPosition(window).x;
						pixel->y = sf::Mouse::getPosition(window).y;
						pixel->r = ui.red->value;
						pixel->g = ui.green->value;
						pixel->b = ui.blue->value;
						connection.SendPacket(pixel);
						break;
					}
					case SQUARE:
						PacketBox box;
						box.type = Packet::e_box;
						box.x = sf::Mouse::getPosition(window).x;
						box.y = sf::Mouse::getPosition(window).y;
						box.w = 10;
						box.h = 10;
						box.r = (rand() % 255);
						box.g = (rand() % 255);
						box.b = (rand() % 255);
						connection.SendPacket(&box);
					}
				}
			}

			heatmap.SetPos(sf::Mouse::getPosition(window));
			heatmap.Update();

			connection.Update(&window);
			ui.Update(&event, &window);

			lastTime = std::chrono::high_resolution_clock::now();

		}
		

		window.clear();

		connection.Render(&window);
		ui.Render(&window);

		window.display();
	}

	//Application has exited


}