#pragma once

#ifndef USER_H_
#define USER_H_

class Server;

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <WS2tcpip.h>

#include "Utilities/Helper.h"
#include "Server.hpp"

class User
{
public:
	User(SOCKET Socket, std::string IP, Server* _server, int playerNum);
	std::string GetName() const { return name; };
	std::string GetIP() const { return ip; };
	SOCKET* GetSocket() { return &socket; };
	void Send(std::string text);
	int GetPlayerNumber() { if (p1) { return 1; } if (p2) { return 2; } }
 
private:
	std::string name;
	std::string ip;
	SOCKET socket;
	Server* server;
	bool p1 = false;
	bool p2 = false;

	void Receive();
	void HandleQuery(std::string* query);
	void SetUserInfo(std::string msg);
	void SendFile(std::string dir, std::string filename);

	bool userInfoDone = false;
};
#endif