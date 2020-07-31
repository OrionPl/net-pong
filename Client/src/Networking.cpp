#define NOMINMAX

#include <windows.h>

#include "Networking.hpp"

Networking::Networking(std::string IP, int Port, std::string Nick, Paddles* _paddles)
{
	ip = IP;
	port = Port;
    nick = Nick;
	paddles = _paddles;

	try
	{
		InitializeWinsock();
		Connect();
		Send("userInfo " + nick);
		receive_thread = std::thread(&Networking::Receive, this);
		receive_thread.detach();
	}
	catch (std::string error)
	{
		std::cout << "Error when connecting to server: " << error << std::endl;
	}
}

Networking::~Networking()
{
	closesocket(Socket);
	WSACleanup();
}

void Networking::InitializeWinsock()
{
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	int wsok = WSAStartup(ver, &wsData);

	if (wsok != 0)
	{
		std::cerr << "SHIT! Can't Initialize winsock!" << std::endl;
	}

	if((Socket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}
}

void Networking::Connect()
{
	sockaddr_in server;

	server.sin_addr.s_addr = inet_addr(ip.c_str());
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	if (connect(Socket , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		std::cout << "SHIT! Could not connect to server! " << WSAGetLastError() << std::endl;
	}
}

void Networking::Send(std::string message)
{
	bool res = send(Socket, message.c_str(), message.size() + 1, 0);

	if (res == SOCKET_ERROR)
		Disconnect();
}

void Networking::Receive()
{
	while (true)
	{
		char buffer[4096];

		int bytesReceived = recv(Socket, buffer, 4096, 0);

		if (bytesReceived > 0)
		{
			std::string received = std::string(buffer, 0, bytesReceived);
			HandleQuery(received);
		}
		else
		{
			Disconnect();
			break;
		}
	}
}

void Networking::HandleQuery(std::string msg)
{
	Helper help;

	if (msg[0] == '$') { // game logic prefix is $
		msg.erase(0, 1); // remove the $ prefix when viewing data

		// splitting data by commas
		std::vector<int> msg_data;
		std::string delimiter = ",";
		std::istringstream ss(msg);
		std::string token;
		std::string::iterator it;
		while(std::getline(ss, token, *(it = delimiter.begin()))) {
			while(*(++it)) ss.get();
			msg_data.push_back(std::stoi(token));
		}
		paddles->SetPaddle(0, msg_data[0], msg_data[1]);
		paddles->SetPaddle(1, msg_data[2], msg_data[3]);

	}
	// else if (msg[0] == "#") {// for initial data, prefix is #. For now it's only for whether the client is p1 or p2
	// 	std::cout << name << "> " << mes << std::endl;
	// }
	else if (help.StringStartsWith(msg, "msgfrom"))
	{
		msg = help.ShortenStringFromLeft(msg, 8);
		std::string name = help.GetStringUntil(msg, "###");
		std::string mes = help.ShortenStringFromLeft(msg, name.length() + 3);

		//if (name != nick)
		std::cout << name << "> " << mes << std::endl;
	}
	else if (help.StringStartsWith(msg, "con"))
	{
		msg = help.ShortenStringFromLeft(msg, 4);

		std::cout << msg << " connected!" << std::endl;
	}
	else if (help.StringStartsWith(msg, "dcon"))
	{
		msg = help.ShortenStringFromLeft(msg, 5);

		std::cout << msg << " disconnected!" << std::endl;
	}
	else
	{
		std::cout << "SERVER> " << msg << std::endl;
	}
}

void Networking::Disconnect()
{
	closesocket(Socket);
	WSACleanup();
}