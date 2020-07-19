#pragma once

#include <chrono>
#include <string>
#include <iostream>

struct Clock
{
    std::chrono::time_point<std::chrono::high_resolution_clock> elapsed;
    std::chrono::time_point<std::chrono::high_resolution_clock> previous_elapsed;
    double dt;

    void tick() {
        elapsed = (std::chrono::high_resolution_clock::now());
        dt = std::chrono::duration<double, std::milli>(elapsed-previous_elapsed).count() / 1000;
        previous_elapsed = elapsed;
    }
};