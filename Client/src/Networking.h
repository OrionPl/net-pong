#pragma once

#ifndef NET_H_
#define NET_H_

#include <windows.h>
#include <thread>

#include "Utilities/Helper.h"

class GameManager;

class Networking
{
public:
	Networking(std::string IP, int Port);
	~Networking();

	void Send(std::string message);
	void RequestFile(std::string filename);

private:
	void Receive();
	void ReceiveFile(std::string fileName);
	void HandleQuery(std::string msg);

	std::string ip;
	int port;

	GameManager* gm;

	bool fileReceived = false;
};
#endif