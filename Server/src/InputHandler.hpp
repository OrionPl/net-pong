#pragma once

#include <iostream>
#include <string>

#include "Settings.hpp"
#include "Utilities/Helper.hpp"
#include "Utilities/Print.h"

void HandleInput(Settings* settings, bool* checkInput)
{
    while (*checkInput)
    {
        std::string input;
        std::getline(std::cin, input);

        Helper help;

        if (settings->can.find(help.GetStringUntil(input, " ")) != settings->can.end())
            ChangeSetting(settings, help.GetStringUntil(input, " "), help.ShortenStringFromLeft(input, help.GetStringUntil(input, " ").size() + 1));
        else
            PRINT "Invalid input" << std::endl;
    }
}