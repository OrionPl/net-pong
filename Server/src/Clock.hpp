#pragma once

#include <ctime>
#include <iostream>

struct Clock
{
    double elapsed;

    void tick() {
        elapsed = (std::clock()) / (double) CLOCKS_PER_SEC;

        std::cout << "elapsed: " << elapsed << "\n";
    }
};