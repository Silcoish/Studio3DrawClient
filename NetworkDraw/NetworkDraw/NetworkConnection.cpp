#include "NetworkConnection.h"

NetworkConnection::NetworkConnection()
{
	start = std::chrono::system_clock::now();
}

NetworkConnection::NetworkConnection(const char* ip, const unsigned int port)
{
	Connect(ip, port);
}

NetworkConnection::~NetworkConnection()
{
	WSACleanup();
}

PacketPixel packetArray[30];

void NetworkConnection::Update(sf::RenderWindow* window)
{

	end = std::chrono::system_clock::now();
	elapsed_seconds = end-start;

	if (elapsed_seconds.count() >= waitTime && connected)
	{
		Listen();
		start = end;
		bool send = (arrayLength > 0) ? true : false;

		//Send mouse pointer
		PacketClientCursor cursor;
		cursor.type = Packet::e_clientCursor;
		cursor.cursor.m_posX = sf::Mouse::getPosition(*window).x;
		cursor.cursor.m_posY = sf::Mouse::getPosition(*window).y;
		cursor.cursor.m_data = *bell;

		int result = sendto(sendSocket, (const char*)&cursor, sizeof(cursor), 0, (SOCKADDR*)&sendAddress, sizeof(sendAddress));
		if (result == SOCKET_ERROR)
		{
			std::cout << "sendto() failed. Update Cursor. Error: " << WSAGetLastError() << std::endl;
		}

		packetsSent++;		

		if (send)
		{
			int result = sendto(sendSocket, (const char*)packetArray, sizeof(*packetArray) * arrayLength, 0, (SOCKADDR*)&sendAddress, sizeof(sendAddress));
			if (result == SOCKET_ERROR)
			{
				std::cout << "sendto() failed. Update Send Packet. Error: " << WSAGetLastError() << std::endl;
			}
			pixelsSent += arrayLength;
			packetsSent++;
			arrayLength = 0;
			std::cout << "Pixels sent: " << pixelsSent << ", Packets sent: " << packetsSent << std::endl;
		}
			
	}

}

void NetworkConnection::Render(sf::RenderWindow* window)
{

	if (connected)
	{
		for (int i = 0; i < mousePositions.size(); i++)
		{
			if (mousePositions[i]->x >= 0 && mousePositions[i]->x < window->getSize().x && mousePositions[i]->y >= 0 && mousePositions[i]->y < window->getSize().y)
			{
				window->draw(*mousePositions[i]->rect);
			}
		}
	}
}

void NetworkConnection::Connect(const char* ip, const unsigned int port)
{
	//Initialise winsock
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << "WSAStartup failed" << std::endl;
	}

	//Create socket

	sendAddress.sin_family = AF_INET;
	sendAddress.sin_port = htons(port);
	sendAddress.sin_addr.S_un.S_addr = inet_addr(ip);


	recvAddress.sin_family = AF_INET;
	recvAddress.sin_port = htons(port);
	recvAddress.sin_addr.S_un.S_addr = INADDR_ANY;

	sendSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (sendSocket == SOCKET_ERROR)
	{
		std::cout << "Error opening socked. Error: " << WSAGetLastError();
		connected = false;
	}
	else
	{
		connected = true;
	}

	PacketClientAnnounce announce;
	announce.type = Packet::e_clientAnnounce;
	int result = sendto(sendSocket, (const char*)&announce, sizeof(announce), 0, (SOCKADDR*)&sendAddress, sizeof(sendAddress));
	if (result == SOCKET_ERROR)
	{
		std::cout << "sendto() failed. Connecting. Error: " << WSAGetLastError() << std::endl;
	}

}

void NetworkConnection::Listen()
{
	if (connected)
	{
		int waiting;
		do
		{
			fd_set checkSockets;
			checkSockets.fd_count = 1;
			checkSockets.fd_array[0] = sendSocket;

			struct timeval t;
			t.tv_sec = 0;
			t.tv_usec = 0;

			waiting = select(NULL, &checkSockets, NULL, NULL, &t);

			if (waiting > 0)
			{
				std::cout << "you have received something" << std::endl;
				int sendAddressSize = sizeof(sendAddress);
				recvfrom(sendSocket, receiveBuffer, sizeof(receiveBuffer), 0, (SOCKADDR*)&sendAddress, &sendAddressSize);
				Packet* packet = (Packet*)receiveBuffer;
				if (packet->type == Packet::e_serverInfo)
				{
					PacketServerInfo* p = (PacketServerInfo*)packet;
					std::cout << "Width: " << p->width << ", Height: " << p->height << std::endl;
					std::cout << "You have announced youself" << std::endl;
				}
				else if (packet->type == Packet::e_serverCursors)
				{
					PacketServerCursors* p = (PacketServerCursors*)packet;
					int mice = 0;
					for (int i = 0; i < p->count; i++)
					{
						std::cout << "X: " << p->cursor[i].m_posX << std::endl;
						std::cout << "Y: " << p->cursor[i].m_posY << std::endl;
						std::cout << "Misc: " << p->cursor[i].m_data << std::endl;
						
						if (i >= mousePositions.size())
						{
							//Create a new one
							mousePositions.push_back(new MousePosition());
							mousePositions[i]->x = p->cursor[i].m_posX;
							mousePositions[i]->y = p->cursor[i].m_posY;
							mousePositions[i]->misc = p->cursor[i].m_data;
							mousePositions[i]->rect = new sf::RectangleShape();
							mousePositions[i]->rect->setPosition(p->cursor[i].m_posX, p->cursor[i].m_posY);
							mousePositions[i]->rect->setFillColor(sf::Color::White);
							mousePositions[i]->rect->setSize(sf::Vector2f(2, 2));
						}
						else
						{
							//edit a current one
							mousePositions[i]->x = p->cursor[i].m_posX;
							mousePositions[i]->y = p->cursor[i].m_posY;
							mousePositions[i]->misc = p->cursor[i].m_data;
							mousePositions[i]->rect->setPosition(mousePositions[i]->x, mousePositions[i]->y);
						}

						mice++;
					}

					std::cout << "Mice received: " << mice << std::endl;
				}
			}
		} while (waiting > 0);
	}
}

void NetworkConnection::ClearScreen()
{

	PacketBox packet;
	packet.type = Packet::e_box;
	packet.x = 0;
	packet.y = 0;
	packet.w = 512;
	packet.h = 512;
	packet.r = ui->red->value;
	packet.g = ui->green->value;
	packet.b = ui->blue->value;

	int result = sendto(sendSocket, (const char*)&packet, sizeof(packet), 0, (SOCKADDR*)&sendAddress, sizeof(sendAddress));
	if (result == SOCKET_ERROR)
	{
		std::cout << "sendto() failed. Clear Screen. Error: " << WSAGetLastError() << std::endl;
	}
}

//PIXEL
void NetworkConnection::SendPacket(PacketPixel *packet)
{
	packetArray[arrayLength] = *packet;
	arrayLength++;

	std::cout << arrayLength << std::endl;
}

//BOX
void NetworkConnection::SendPacket(PacketBox *packet)
{

	packet->r = ui->red->value;
	packet->g = ui->green->value;
	packet->b = ui->blue->value;

	int result = sendto(sendSocket, (const char*)packet, sizeof(*packet), 0, (SOCKADDR*)&sendAddress, sizeof(sendAddress));
	if (result == SOCKET_ERROR)
	{
		std::cout << "sendto() failed. BOX Error: " << WSAGetLastError() << std::endl;
	}
}