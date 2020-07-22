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
	User(SOCKET Socket, std::string IP, Server* _server);
	std::string GetName() const { return name; };
	std::string GetIP() const { return ip; };
	SOCKET* GetSocket() { return &socket; };
	void Send(std::string text);

private:
	std::string name;
	std::string ip;
	SOCKET socket;
	Server* server;

	void Receive();
	void HandleQuery(std::string* query);
	void SetUserInfo(std::string msg);
	void SendFile(std::string dir, std::string filename);

	bool userInfoDone = false;
};
#endif