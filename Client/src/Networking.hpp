#pragma once

#ifndef NET_H_
#define NET_H_

//#include <windows.h>
#include <thread>
#include <WS2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")

#include "Utilities/Helper.h"

class GameManager;

class Networking
{
public:
	Networking(std::string IP, int Port, std::string Nick);
	~Networking();

	void Send(std::string message);

private:
	void InitializeWinsock();
	void Connect();
	void Receive();
	void HandleQuery(std::string msg);
	void Disconnect();

	SOCKET Socket;

	std::string ip;
	int port;
	std::string nick;
};
#endif