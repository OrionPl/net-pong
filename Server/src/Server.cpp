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
		if (users[i]->GetName() == user->GetName())
		{
			users.erase(users.begin() + i);
		}
	}

	users.shrink_to_fit();

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
}

void Server::AddUser(User* user)
{
	users.push_back(user);
	SendToAllUsersBesidesThis("con " + user->GetName(), user);
	std::cout << user->GetName() << " connected" << std::endl;
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