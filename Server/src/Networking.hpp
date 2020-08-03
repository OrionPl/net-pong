#pragma once

#include <thread>
#include <vector>
#include <iostream>
#include <WS2tcpip.h>

#include "Utilities/Print.h"

#include "Server.hpp"
#include "Logic.hpp"
#include "Settings.hpp"

#pragma comment (lib, "ws2_32.lib")

class Networking {
public:
    Networking(Settings* _settings, Logic* logic);
    ~Networking();

    Server* GetServer() { return server; };
    SOCKET* GetSocket() { return &listenSock; };

private:
    SOCKET listenSock;
    Server* server;
    Settings* settings;

    std::thread main_network_thread;

    void InitializeWinsock();
    void CreateServerSocket(Logic* _logic);
    void BindSocketToPort(int port);
    void StartListeningThread();
    void StartListening();
    void AcceptIncomingConnections();
};