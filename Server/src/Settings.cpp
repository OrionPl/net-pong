#include "Settings.hpp"

void LoadSettings(Settings* settings) {
    std::ifstream in("Server.variables");
    std::string line;
    while (std::getline(in, line)) {
        std::string variable_name;
        std::string value = line;

        int i = 0;
        while (line[i] != ' ') {
            variable_name += line[i];
            value.erase(0, 1);
            i++;
        }
        // remove space seperator
        value.erase(0, 1);

        switch (value[0]) {
            // bool
            case 't':
                (*settings).can[variable_name] = true;
                break;
            case 'f':
                (*settings).can[variable_name] = false;
                break;
            // otherwise just int for now
            default:
                (*settings).valueof[variable_name] = std::stoi(value);
                break;
        }
    }
}

void ChangeSetting(Settings* settings, std::string setting, std::string value) {
    if (value == "true")
        settings->can[setting] = true;
    else if (value == "false")
        settings->can[setting] = false;
    else
        PRINT "Invalid setting value!" << std::endl;
}