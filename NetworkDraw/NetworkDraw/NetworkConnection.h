#ifndef NETWORKCONNECTION_H
#define NETWORKCONNECTION_H
#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "Packet.h"
#include "UI.h"
#include "MousePosition.h"

#define SIZE 512

class NetworkConnection
{
private:
	char* ip;
	unsigned int port;
	sockaddr_in sendAddress;
	sockaddr_in recvAddress;
	SOCKET sendSocket;

	char receiveBuffer[1024];
	int bufferLength = 1024;

	int arrayLength = 0;

	const char* bell = "\sa";

	//time tracking
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;
	float waitTime = 0.3f;

	std::vector<MousePosition*> mousePositions;

public:
	UI* ui;

	unsigned int pixelsSent = 0;
	unsigned int packetsSent = 0;
public:
	bool connected = false;
public:
	NetworkConnection();
	NetworkConnection(const char* ip, const unsigned int port);
	~NetworkConnection();
	void Update(sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
	void Connect(const char* ip, const unsigned int port);
	void Listen();
	void SendPacket(PacketPixel *packet);
	void SendPacket(PacketBox *packet);
	void ClearScreen();
};

#endif