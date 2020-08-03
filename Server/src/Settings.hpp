#pragma once

#include <map>
#include <string>
#include <fstream>

#include "Utilities/Print.h"

struct Settings {
    std::map<std::string, bool> can;
    std::map<std::string, int> valueof;
};

void LoadSettings(Settings* settings);
void ChangeSetting(Settings* settings, std::string setting, std::string value);