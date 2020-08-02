#include "Server.hpp"

Server::Server(SOCKET* serverSock, Logic* _logic)
{
	serverSocket = serverSock;
	logic = _logic;
	send_to_users_thread = std::thread();
}

void Server::OnConnect(SOCKET clientSock, sockaddr_in* client)
{
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];

	if (getnameinfo((sockaddr*)& client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		std::cout << host << " connected on port " << service << std::endl;
	}
	else
	{
		//inet_ntop(AF_INET, &client->sin_addr, host, NI_MAXHOST); //DOES NOT WORK WITH MINGW????????
		std::cout << host << " connected to port " << ntohs(client->sin_port) << std::endl;
	}


	new User(clientSock, host, this);
}

void Server::OnDisconnect(User* user)
{
	std::cout << user->GetName() << " disconnected" << std::endl;
	SendToAllUsers("dcon " + user->GetName());

	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->GetName() == user->GetName()) {
			users.erase(users.begin() + i);
			break;
		}
	}

	users.shrink_to	_fit();

	if (users.empty())
	{
		std::cout << std::endl << "Noone is connected" << std::endl;
	}
	else
	{
		for (int i = 0; i < users.size(); i++)
		{
			std::cout << users[i]->GetName() << " is connected" << std::endl;
		}
	}

	user->~User();
}

void Server::AddUser(User* user)
{
	users.push_back(user);
	SendToAllUsersBesidesThis("con " + user->GetName(), user);
	std::cout << user->GetName() << " connected" << std::endl;
}

std::string Server::ConfirmUsername(std::string proposed_username) {

	// if there's a duplicate username, it keeps adding "-1" until it's a unique username. e.g. There could be "orion" and "orion-1", and another user called orion wanted to join, they would keep adding "-1" until it was unique, therefore making the new user be called "orion-1-1". Not the cleanest, but works.

	for (unsigned int i = 0; i < users.size()) {
		if (proposed_username == users[i].GetName()) {
			return ConfirmUsername(proposed_username + "-1");
		}
	}

	return proposed_username
}


void Server::SendToAllUsers(std::string message)
{
	for (int i = 0; i < users.size(); i++)
	{
		users[i]->Send(message);
	}
}

void Server::SendToAllUsersBesidesThis(std::string message, User* user)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->GetSocket() != user->GetSocket())
			users[i]->Send(message);
	}
}

Logic* Server::GetLogic() {
	return logic;
}