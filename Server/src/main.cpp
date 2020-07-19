#include <iostream>

#include "Networking.hpp"
#include "Server.hpp"

#include "Logic.hpp"

int main(int argc, char*[])
{
    Networking* net = new Networking(66666);
    Server* serv = net->GetServer();

    Logic logic;

    while (true) {
        logic.update();
    }

    return 0;
}