#include "SettingsControl.hpp"

void SettingsControl::LoadSettings() {
    std::ifstream in("src/Server.variables");
    std::string line;
    while (std::getline(in, line)) {
        std::string variable_name;
        std::string value = line;
        // Creates variable name while it hasn't found a space, when it finds the space, it finishes, and then assigns the value.
        // [i - 1] so that the space can be erased from value.
        int i = 0;
        while (line[i - 1] != ' ') {
            variable_name += line[i];
            value.erase(0, 1);
            i++;
        }

        PRINT variable_name << "\n";
        PRINT value << "\n";
    }
}

int SettingsControl::GetPort() { return port; }
bool SettingsControl::LogInits() { return log_inits; }
bool SettingsControl::LogOnDisconnect() { return log_on_disconnect; }
bool SettingsControl::LogOnConnect() { return log_on_connect; }
bool SettingsControl::ReloadConnectedAfterDisconnect() { return relog_connected_after_disconnect; }
bool SettingsControl::LogClientMsg() { return log_client_msg; }