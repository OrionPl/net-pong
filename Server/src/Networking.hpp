#pragma once

#include <thread>
#include <vector>
#include <iostream>
#include <WS2tcpip.h>

#include "Server.hpp"

#pragma comment (lib, "ws2_32.lib")

class Networking {
public:
    Networking(int port);

    Server* GetServer() { return server; };

private:
    SOCKET listenSock;
    Server* server;

    std::thread main_network_thread;

    void InitializeWinsock();
    void CreateServerSocket();
    void BindSocketToPort(int port);
    void StartListeningThread();
    void StartListening();
    void AcceptIncomingConnections();
};