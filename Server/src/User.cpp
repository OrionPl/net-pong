#include "User.hpp"

User::User(SOCKET Socket, std::string IP, Server* _server) {
	socket = Socket;
	ip = IP;
	server = _server;
	userInfoDone = false;
	player_index = server->GetLogic()->NewPlayer_GetIndex();

	// receive thread starts in receive user info,
	// then runs SetUserInfo. if SetUserInfo runs successfully, it
	// runs Receive_General
	receive_thread = std::thread(&User::Receive_UserInfo, this);
	receive_thread.detach();
}

void User::Receive_General() {
	while (true) {
		char buffer[4096];
		int bytesReceived = recv(socket, buffer, 4096, 0);

		if (bytesReceived > 0) {
			server->GetLogic()->TakeInput(player_index, std::string(buffer, 0, bytesReceived));
		}
		else {
			server->GetLogic()->RemovePlayer(player_index);
			server->OnDisconnect(this);
			break;
		}
	}
}

void User::Receive_UserInfo() {
	while (true) {

		char buffer[4096];
		int bytesReceived = recv(socket, buffer, 4096, 0);

		if (bytesReceived > 0) {
			SetUserInfo(std::string(buffer, 0, bytesReceived));
		}
		else {
			server->GetLogic()->RemovePlayer(player_index);
			server->OnDisconnect(this);
			break;
		}
	}
}

void User::SetUserInfo(std::string msg) {

	if (!Helper::StringStartsWith(msg, "userInfo")) {
		if (server->settings->can["log_on_disconnect"])
			PRINT "Kicking " + ip + " for not giving info about their client\n" + msg;
		closesocket(socket);
	}
	else if (Helper::StringStartsWith(msg, "userInfo")) {
		for (int i = 9; i < msg.length(); i++) {
			msg[i - 9] = msg[i];
			msg[i] = ' ';
		}

		msg.resize(msg.length() - 9);

		if (server->settings->can["log_on_connect"])
			PRINT name + " set nickname to " + msg + "\n";
		name = msg;

		userInfoDone = true;
		server->AddUser(this);

		std::vector<User*> users = *(server->GetUsers());

		for (int i = 0; i < users.size(); i++) {
			Send("con " + users[i]->GetName());
		}

		Receive_General();
	}
}

void User::Send(std::string text) {
	send(socket, text.c_str(), text.size() + 1, 0);
}