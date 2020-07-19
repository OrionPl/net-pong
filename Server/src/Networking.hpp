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
    ~Networking();

    Server* GetServer() { return server; };
    SOCKET* GetSocket() { return &listenSock; };

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