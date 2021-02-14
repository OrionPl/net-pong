#define NOMINMAX

#include <windows.h>
#include <cstdint>

#include "Networking.hpp"
#include "NMessages.hpp"

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
		uint64_t msgSize;
		char sizeBuf[sizeof(uint64_t)];

		int sizeSize = recv(Socket, sizeBuf, sizeof(uint64_t), 0);

		msgSize = (uint64_t)sizeBuf;

		char buffer[msgSize];

		int bytesReceived = recv(Socket, buffer, msgSize, 0);

		if (bytesReceived > 0) {
			NetworkMessage received;
			received.SetData((void*)buffer);
			received.SetDataSize(msgSize);

			HandleQuery(received);
		}
		else {
			Disconnect();
			break;
		}
	}
}

void Networking::HandleQuery(NetworkMessage msg) {

	if (sizeof(msg) < sizeof(uint8_t)) {
		PRINT "Got garbage network message from server.";
	}
	
	MessageType msgType = (MessageType)(*(uint8_t*)msg.GetData());
	
	switch (msgType) {
		case mt_basic:
		break;
		
		case mt_movement:
		if (msg.GetDataSize() == sizeof(Msg_Movement)) {
			Msg_Movement* _msg = (Msg_Movement*)msg.GetData();
			
			paddles->SetPaddles(_msg->GetPaddle1_x(), _msg->GetPaddle1_y(), _msg->GetPaddle2_x(), _msg->GetPaddle2_y());
			ball->SetPosition(_msg->GetBall_x(), _msg->GetBall_y());
		}
		break;

		case mt_chatMsg:
		if (msg.GetDataSize() == sizeof(Msg_ChatMsg)) {
			Msg_ChatMsg* _msg = (Msg_ChatMsg*)msg.GetData();
			
			PRINT "> " << _msg->GetChatMsg() << "\n";
		}
		break;

		case mt_connect:
		if (msg.GetDataSize() == sizeof(Msg_Connect)) {
			Msg_Connect* _msg = (Msg_Connect*)msg.GetData();
			
			PRINT _msg->GetName() << " connected!\n";
		}
		break;
		
		case mt_disconnect:
		if (msg.GetDataSize() == sizeof(Msg_Disconnect)) {
			Msg_Disconnect* _msg = (Msg_Disconnect*)msg.GetData();
			
			PRINT _msg->GetName() << " disconnected!\n";
		}
		break;
	}
}

void Networking::Disconnect() {
	closesocket(Socket);
}