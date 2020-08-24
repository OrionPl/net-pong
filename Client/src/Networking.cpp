#define NOMINMAX

#include <windows.h>

#include "Networking.hpp"

Networking::Networking(Paddles* _paddles, Ball* _ball) {
	paddles = _paddles;
	ball = _ball;
	InitializeWinsock();
}

Networking::~Networking() {
	closesocket(Socket);
	WSACleanup();
}

void Networking::InitializeWinsock() {
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	int wsok = WSAStartup(ver, &wsData);

	if (wsok != 0) {
		PRINT "SHIT! Can't Initialize winsock!\n";
	}

	if((Socket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET) {
		printf("Could not create socket : %d" , WSAGetLastError());
	}
}

bool Networking::Connect(std::string IP, int Port, std::string Nick) {
	ip = IP;
	port = Port;
    nick = Nick;

	try {

		sockaddr_in server;

		server.sin_addr.s_addr = inet_addr(ip.c_str());
		server.sin_family = AF_INET;
		server.sin_port = htons(port);

		if (connect(Socket , (struct sockaddr *)&server , sizeof(server)) < 0) {
			SDL_Log("SHIT! Could not connect to server! %i\n", WSAGetLastError());
		}
		else {
			SDL_Log("ALL GOOD\n");
		}

		receive_thread = std::thread(&Networking::Receive, this);
		receive_thread.detach();
		Send("userInfo " + nick);

		return true;
	}
	catch (std::string error) {
		PRINT "Error when connecting to server: " + error + "\n";
		return false;
	}
}

void Networking::Send(std::string message) {
	bool res = send(Socket, message.c_str(), message.size() + 1, 0);

	if (res == SOCKET_ERROR)
		Disconnect();
}

void Networking::Receive() {
	while (true) {
		char buffer[4096];

		int bytesReceived = recv(Socket, buffer, 4096, 0);

		if (bytesReceived > 0) {
			std::string received = std::string(buffer, 0, bytesReceived);
			HandleQuery(received);
		}
		else {
			Disconnect();
			break;
		}
	}
}

void Networking::HandleQuery(std::string msg) {
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
		paddles->SetPaddles(msg_data[0], msg_data[1], msg_data[2], msg_data[3]);
		ball->SetPosition(msg_data[4], msg_data[5]);
	}
	else if (help.StringStartsWith(msg, "msgfrom")) {
		msg = msg.substr(0, 8);
		std::string name = help.GetStringUntil(msg, "###");
		std::string mes = msg.substr(0, name.length() + 3);

		//if (name != nick)
		PRINT name + "> " + mes + "\n";
	}
	else if (help.StringStartsWith(msg, "con")) {
		msg = msg.substr(0, 4);

		PRINT msg + " connected!\n";
	}
	else if (help.StringStartsWith(msg, "dcon")) {
		msg = msg.substr(0, 5);

		PRINT msg << " disconnected!\n";
	}
	else {
		PRINT "SERVER> " + msg + "\n";
	}
}

void Networking::Disconnect() {
	closesocket(Socket);
}