#define NOMINMAX

#include <windows.h>

#include "Networking.h"

Networking::Networking(std::string IP, int Port, GameManager* Gm)
{
	ip = IP;
	port = Port;
	gm = Gm;

	try
	{
		socket.connect(ip, port);

		Send("userInfo " + "orion?");
		std::thread receiveThread(&Networking::Receive, this);
		receiveThread.detach();
	}
	catch (std::string error)
	{
		std::cout << "Error when connecting to server: " << error << std::endl;
	}
}

void Networking::Send(std::string message)
{
	socket.send(message.c_str(), message.size() + 1);
}

void Networking::RequestFile(std::string filename)
{
	std::cout << "Requesting file " << filename << std::endl;;
	Send("getfile " + filename);

	while (!fileReceived)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	std::cout << "File successfully received" << std::endl;
	fileReceived = false;
}

void Networking::Receive()
{
	char buffer[4096];

	while (true)
	{
		ZeroMemory(buffer, 4096);

		std::size_t bytesReceived = 0;
		socket.receive(buffer, sizeof(buffer), bytesReceived);

		if (bytesReceived > 0)
		{
			std::string received = std::string(buffer, 0, bytesReceived);
			std::cout << "Rec: " << received << std::endl;
			HandleQuery(received);
		}
		else
		{
			std::cout << "SHIT! Disconnected from server!" << std::endl;
			socket.disconnect();
			return;
		}
	}
}

void Networking::HandleQuery(std::string msg)
{
	Helper help;

	if (help.StringStartsWith(msg, "msgfrom"))
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