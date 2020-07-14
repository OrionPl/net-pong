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

private:
    SOCKET listenSock;
    Server* server;

    void InitializeWinsock();
    void CreateServerSocket();
    void BindSocketToPort(int port);
    void StartListening();
    void AcceptIncomingConnections();
};