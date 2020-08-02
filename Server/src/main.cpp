#pragma once

#include <map>

#include "Utilities/Print.h"

#include "SettingsControl.hpp"
#include "Networking.hpp"
#include "Server.hpp"

#include "Logic.hpp"

int main(int argc, char*[]) {
    SettingsControl settings_control;
    settings_control.LoadSettings();
    Logic logic;
    Networking net(55555, &logic);
    Server* serv = net.GetServer();

    while (true) {
        logic.Update();
        serv->SendToAllUsers(logic.GetNetworkMsg());
        //PRINT logic.GetNetworkMsg() + "\n";
    }

    return 0;
}