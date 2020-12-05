#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include "Text.hpp"
#include "GlobalWindowData.hpp"

struct Item {
    SDL_Texture* texture1; // normal texture
    SDL_Texture* texture2; // texture with underline
    SDL_Rect     rect;
    int font_size;
    char* str;
    bool hover;
};

struct Menu {
    Menu(Text* _text);
    void Draw();
    void Update();
    void MousePressed(int x, int y);

    void inline AddText(char* str, int font_size, int x, int y) {
        Item item;
        item.texture1 = text->CreateTexture(g_data.rdr, str, font_size);
        item.texture2 = text->CreateTexture(g_data.rdr, str, font_size, true);
        SDL_QueryTexture(item.texture1, NULL, NULL, & item.rect.w, & item.rect.h);
        item.font_size = font_size;
        item.str = str;
        item.rect.x = x; item.rect.y = y;
        item.hover = false;

        items.push_back(item);
    }

    Text* text;

    std::vector<Item> items;
};