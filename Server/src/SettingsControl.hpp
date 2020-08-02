#pragma once

#include <fstream>
#include <string>

#include "Utilities/Print.h"

class SettingsControl {
public:
    void LoadSettings();
    int GetPort();
    bool LogInits();
    bool LogOnDisconnect();
    bool LogOnConnect();
    bool ReloadConnectedAfterDisconnect();
    bool LogClientMsg();
private:
    int port;
    bool log_inits;
    bool log_on_disconnect;
    bool log_on_connect;
    bool relog_connected_after_disconnect;
    bool log_client_msg;
};