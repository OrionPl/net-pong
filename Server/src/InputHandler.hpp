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

        if (settings->can.find(Helper::GetStringUntil(input, " ")) != settings->can.end())
            ChangeSetting(settings, Helper::GetStringUntil(input, " "), Helper::ShortenStringFromLeft(input, Helper::GetStringUntil(input, " ").size() + 1));
        else
            PRINT "Invalid input" << std::endl;
    }
}