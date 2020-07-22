#pragma once

#ifndef NET_H_
#define NET_H_

//#include <windows.h>
#include <thread>
#include <sstream>
#include <WS2tcpip.h>
#include <SDL2/SDL.h>

#pragma comment (lib, "Ws2_32.lib")

#include "Utilities/Helper.h"

#include "Paddles.hpp"

class Networking
{
public:
	Networking(std::string IP, int Port, std::string Nick, Paddles* _paddles);
	~Networking();

	void Send(std::string message);

private:
	void InitializeWinsock();
	void Connect();
	void Receive();
	void HandleQuery(std::string msg);
	void Disconnect();

	std::thread receive_thread;

	SOCKET Socket;

	std::string ip;
	int port;
	std::string nick;


	Paddles* paddles;
};
#endif