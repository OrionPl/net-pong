#pragma once

#include <thread>

#include "Utilities/Helper.hpp"
#include "Utilities/Print.h"

#include "Settings.hpp"
#include "Networking.hpp"
#include "Server.hpp"
#include "Logic.hpp"
#include "InputHandler.hpp"

int main(int argc, char*[]) {

    Settings settings;
    LoadSettings(&settings);

    bool run = true;
    std::thread inputThread(&HandleInput, &settings, &run);

    Logic logic;
    Networking net(&settings, &logic);
    Server* serv = net.GetServer();

    while (true) {
        logic.Update();
        serv->SendToAllUsers(logic.GetNetworkMsg());
        //PRINT logic.GetNetworkMsg() + "\n";
    }

    return 0;
}