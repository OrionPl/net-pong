#pragma once

#include <map>
#include <string>
#include <fstream>

struct Settings {
    std::map<std::string, bool> can;
    std::map<std::string, int> valueof;
};

void LoadSettings(Settings* settings);