#pragma once

#ifndef SERVER_H_
#define SERVER_H_

class User;

#include <WS2tcpip.h>
#include <vector>
#include <string>

#include "User.hpp"
#include "Logic.hpp"
#include "Settings.hpp"

class Server {
public:
	Server(SOCKET* serverSock, Logic* _logic, Settings* _settings);
	void OnConnect(SOCKET clientSock, sockaddr_in* client);
	void OnDisconnect(User* user);
	void AddUser(User* user);
	std::string ConfirmUsername(std::string proposed_username);
	void SendToAllUsers(std::string message);
	void SendToAllUsersBesidesThis(std::string message, User* user);

	std::vector<User*>* GetUsers() { return &users; };

	Logic* GetLogic();

	Settings* settings;

private:
	SOCKET* serverSocket;
	std::thread send_to_users_thread;
	std::vector<User*> users;
	Logic* logic;

	bool p1connected = false;
	bool p2connected = false;
};
#endif