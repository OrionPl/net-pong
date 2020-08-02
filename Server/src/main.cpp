#include <iostream>

#include "Networking.hpp"
#include "Server.hpp"

#include "Logic.hpp"

int main(int argc, char*[]) {
    Logic logic;
    Networking net(66666, &logic);
    Server* serv = net.GetServer();

    while (true) {
        logic.Update();
        serv->SendToAllUsers(logic.GetNetworkMsg());
        std::cout << logic.GetNetworkMsg() << std::endl;
    }

    return 0;
}