#pragma once

#ifndef NET_H_
#define NET_H_

//#include <windows.h>
#include <thread>
#include <sstream>
#include <WS2tcpip.h>
#include <SDL2/SDL.h>

#pragma comment (lib, "Ws2_32.lib")

#include "Utilities/Helper.hpp"
#include "Utilities/Print.hpp"

#include "Paddles.hpp"
#include "Ball.hpp"

class Networking
{
public:
	Networking(Paddles* _paddles, Ball* _ball);
	~Networking();

	bool Connect(std::string IP, int Port, std::string Nick);
	void Send(std::string message);

	void Disconnect();
private:
	void InitializeWinsock();
	void Receive();
	void HandleQuery(std::string msg);

	std::thread receive_thread;

	SOCKET Socket;

	std::string ip;
	int port;
	std::string nick;


	Paddles* paddles;
	Ball* ball;
};
#endif