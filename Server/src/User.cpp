#include "User.hpp"
#include "Server.hpp"

User::User(SOCKET Socket, std::string IP, Server* _server) {
	socket = Socket;
	ip = IP;
	server = _server;
	userInfoDone = false;
	player_index = server->GetLogic()->NewPlayer_GetIndex();

	std::thread receiveThread(&User::Receive, this);
	receiveThread.detach();
}

void User::Receive() {
	while (true) {
		char buffer[4096];

		int bytesReceived = recv(socket, buffer, 4096, 0);

		if (bytesReceived > 0) {
			std::string msg = std::string(buffer, 0, bytesReceived);

			if (!userInfoDone) {
				SetUserInfo(msg);
			}
			else {
				server->GetLogic()->TakeInput(player_index, msg);
			}
		}
		else {
			server->GetLogic()->RemovePlayer(player_index);
			server->OnDisconnect(this);
			break;
		}
	}
}

void User::SetUserInfo(std::string msg) {
	Helper help;

	if (!help.StringStartsWith(msg, "userInfo")) {
		closesocket(socket);
	}
	else if (help.StringStartsWith(msg, "userInfo")) {
		for (int i = 9; i < msg.length(); i++) {
			msg[i - 9] = msg[i];
			msg[i] = ' ';
		}

		msg.resize(msg.length() - 9);

		PRINT name + " set nickname to " + msg + "\n";
		name = msg;

		userInfoDone = true;
		server->AddUser(this);

		std::vector<User*> users = *(server->GetUsers());

		for (int i = 0; i < users.size(); i++) {
			Send("con " + users[i]->GetName());
		}
	}
}

void User::SendFile(std::string dir, std::string filename) {
	std::ifstream file(dir);
	std::string line;

	if (!file) return;


	Send("FILENAME " + filename);

	while (std::getline(file, line)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
		Send(line);
	}

	file.close();

	Send("#EOF");
}

void User::Send(std::string text) {
	send(socket, text.c_str(), text.size() + 1, 0);
}