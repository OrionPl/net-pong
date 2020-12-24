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

struct TextBox {
    SDL_Texture* texture;
    SDL_Rect rect;
    int font_size;
    std::string defaultText;
    std::string* currText;
    bool hover;
    bool selected;
    Text* txt;

    void Select() {
        selected = true;
    }

    void UnSelect() {
        selected = false;
    }

    void ChangeText(std::string text) {
        *currText = text;
        texture = txt->CreateTexture(g_data.rdr, text, font_size);
        SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

        //then if selected draw a line to where the user is typing|
    }

    void Draw() {
        SDL_RenderCopy(g_data.rdr, texture, NULL, &rect);
        SDL_RenderDrawRect(g_data.rdr, &rect);
    }
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

    void inline AddTextBox(std::string defaultText, int font_size, int x, int y, int w, std::string* txt) {
        TextBox text_box = {
            text->CreateTexture(g_data.rdr, defaultText, font_size),
            {x, y, w, y + font_size},
            font_size,
            defaultText,
            txt,
            false,
            false,
            text
        };
        SDL_QueryTexture(text_box.texture, NULL, NULL, & text_box.rect.w, & text_box.rect.h);

        text_boxes.push_back(text_box);
    }

    Text* text;
    TextBox* selected_text_box = nullptr;

    std::vector<Item> items;
    std::vector<TextBox> text_boxes;
};