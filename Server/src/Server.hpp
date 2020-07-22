#pragma once

#ifndef SERVER_H_
#define SERVER_H_

class User;

#include <WS2tcpip.h>
#include <vector>
#include <string>

#include "User.hpp"
#include "Logic.hpp"

class Server
{
public:
	Server(SOCKET* serverSock, Logic* _logic);
	void OnConnect(SOCKET clientSock, sockaddr_in* client);
	void OnDisconnect(User* user);
	void AddUser(User* user);
	void SendToAllUsers(std::string message);
	void SendToAllUsersBesidesThis(std::string message, User* user);

	std::vector<User*>* GetUsers() { return &users; };

	Logic* GetLogic();

private:
	SOCKET* serverSocket;
	std::thread send_to_users_thread;
	std::vector<User*> users;
	Logic* logic;
};
#endif