#pragma once

#include <vector>
#include <string>

#include <SDL2/SDL.h>

#include "Text.hpp"
#include "GlobalData.hpp"

struct Item {
    SDL_Texture* texture; // normal texture
    SDL_Rect     rect;
    int font_size;
    std::string str;
    bool hover;
    bool can_underline;
    void (* eventHandler)();
};

struct Menu {
    Menu(Text* _text);
    void Draw();
    void Update();
    void MousePressed(int x, int y);

     void inline AddText(std::string str, int font_size, int x, int y, bool can_underline = false, void (* eventHandler)()=nullptr) {

        Item item = {
            text->CreateTexture(g_data.rdr, str, font_size),
            {x, y, -1, -1},
            font_size,
            str,
            false,
            can_underline,
            eventHandler
        };
        SDL_QueryTexture(item.texture, NULL, NULL, & item.rect.w, & item.rect.h);

        items.push_back(item);
    }

    Text* text;

    std::vector<Item> items;
};