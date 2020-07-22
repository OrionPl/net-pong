#include "Networking.hpp"

Networking::Networking(int port, Logic* _logic)
{
    InitializeWinsock();
	CreateServerSocket(_logic);
	BindSocketToPort(port);
	StartListeningThread();

	// closesocket(listenSock);
	// WSACleanup();
}

Networking::~Networking()
{
	closesocket(listenSock);
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
}

void Networking::CreateServerSocket(Logic* _logic)
{
	listenSock = socket(AF_INET, SOCK_STREAM, 0);

	if (listenSock == INVALID_SOCKET)
	{
		std::cerr << "SHIT! Can't create a socket!" << std::endl;
	}

	server = new Server(&listenSock, _logic);
}

void Networking::BindSocketToPort(int port)
{
	std::cout << "Binding to port " << port << std::endl;

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listenSock, (sockaddr*)& hint, sizeof(hint));
}

void Networking::StartListeningThread() {
	main_network_thread = std::thread(&Networking::StartListening, this);
}

void Networking::StartListening()
{
	std::cout << "Starting listening" << std::endl;

	int maxConnections = 2;

	listen(listenSock, maxConnections);

	std::cout << "Waiting for connections..." << std::endl;

	AcceptIncomingConnections();
}

void Networking::AcceptIncomingConnections()
{
	while (true)
	{
		sockaddr_in client;
		int clientSize = sizeof(client);

		SOCKET newSocket = accept(listenSock, (sockaddr*)& client, &clientSize);

		if (newSocket == INVALID_SOCKET)
		{
			std::cout << "SHIT! Invalid socket error: " << WSAGetLastError() << std::endl;
		}
		else
		{
			std::thread connectionHandler(&Server::OnConnect, server, newSocket, &client);
			connectionHandler.detach();
		}
	}
}