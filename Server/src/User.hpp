#pragma once

class Server;

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <WS2tcpip.h>

#include "Utilities/Helper.hpp"
#include "Utilities/Print.h"
#include "Server.hpp"
#include "Settings.hpp"

class User {
public:
	User(SOCKET Socket, std::string IP, Server* _server);
	~User() { };
	std::string GetName() const { return name; };
	std::string GetIP() const { return ip; };
	SOCKET* GetSocket() { return &socket; };
	void Send(std::string text);

private:
	std::string name;
	std::string ip;
	SOCKET socket;
	Server* server;

	void Receive_General();
	void Receive_UserInfo();
	void HandleQuery(std::string* query);
	void SetUserInfo(std::string msg);

	std::thread receive_thread;

	bool userInfoDone = false;
	int player_index;
};