#include "Menu.hpp"

Menu::Menu(Text* _text) {
    text = _text;

    AddText("Net Pong", 35, 15, 15);
    AddText("Connect", 35, 15, 155, true);
}

void Menu::Draw() {
    for (unsigned int i = 0; i < items.size(); i++) {
        SDL_RenderCopy(g_data.rdr, items[i].texture, NULL, & items[i].rect);

        if (items[i].hover && items[i].can_underline) {
           SDL_Rect rect = items[i].rect;
           rect.y += rect.h * 0.8;
           rect.h = 5;
           SDL_RenderFillRect(g_data.rdr, & rect);
        }
    }
}

void Menu::Update() {
    for (int i = 0; i < items.size(); i ++) {
        items[i].hover = g_data.mx > items[i].rect.x && g_data.mx < items[i].rect.x + items[i].rect.w && g_data.my > items[i].rect.y && g_data.my < items[i].rect.y + items[i].rect.h;
    }
}

void Menu::MousePressed(int x, int y) {
    // for (int i : button_indexes) {
    //     if (x > text_rects[i].x && x < text_rects[i].x + text_rects[i].w && y > text_rects[i].y && y < text_rects[i].y + text_rects[i].h) {
    //         // do some shit
    //     }
    // }
}