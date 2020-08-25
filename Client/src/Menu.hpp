#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include "GlobalWindowData.hpp"
#include "Text.hpp"

struct Items {
    std::vector<int> xs;
    std::vector<int> ys;
    std::vector<int> ws;
    std::vector<int> hs;
    std::vector<SDL_Texture*> textures;
    std::vector<void(*)()> functions;
};

class Menu {
public:
    Menu();
    void Draw();
    void MousePressed(int x, int y);
    void DestroyTextures();
private:
    inline void AddItem(int x, int y, int w, int h, std::string text, void(*function)());
    Items items;
};

// TO MIKOLAJ: MAYBE ADD CHEEKY PRIVATE FUNCTIONS LIKE STARTMAINMENU(), SETTINGSMENU(), etc...
// YOU CAN CLEAR BY DOING: items = {};