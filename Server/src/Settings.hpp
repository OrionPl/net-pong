#pragma once

#include <map>
#include <string>
#include <fstream>

struct Settings {
    std::map<std::string, bool> can;
    std::map<std::string, int> valueof;
};

void LoadSettings(Settings* settings) {
    std::ifstream in("src/Server.variables");
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