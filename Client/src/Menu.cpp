#include "Menu.hpp"

void Test1() {
    SDL_Log("test1");
}

Menu::Menu(Text* _text) {
    text = _text;

    AddText("Connect", 35, 15, 155, true, &Test1);
    AddText("Net Pong", 35, 15, 15);
    AddTextBox("textbox", 35, 60, 60, 120, new std::string);

}

void Menu::Draw() {
    for (unsigned int i = 0; i < items.size(); i++) {
        SDL_RenderCopy(g_data.rdr, items[i].texture, NULL, & items[i].rect);

        // underline buttons on hover
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

    for (int i = 0; i < text_boxes.size(); i ++) {
        text_boxes[i].hover = g_data.mx > text_boxes[i].rect.x && g_data.mx < text_boxes[i].rect.x + text_boxes[i].rect.w && g_data.my > text_boxes[i].rect.y && g_data.my < text_boxes[i].rect.y + text_boxes[i].rect.h;
    }
}

void Menu::MousePressed(int x, int y) {
    // for (int i : button_indexes) {
    //     if (x > text_rects[i].x && x < text_rects[i].x + text_rects[i].w && y > text_rects[i].y && y < text_rects[i].y + text_rects[i].h) {
    //         // do some shit
    //     }
    // }

    for (int i = 0; i < items.size(); i++) {
        if (items[i].hover && items[i].event_handler) items[i].event_handler();
    }

    bool selected = false;

    for (int i = 0; i < text_boxes.size(); i++) {
        if (text_boxes[i].hover) {
            selected_text_box->selected = false;
            selected_text_box = &text_boxes[i];
            selected_text_box->selected = true;
            selected = true;

            SDL_StopTextInput();
            SDL_StartTextInput();
        }
    }

    if (!selected) {
        selected_text_box = nullptr;
        SDL_StopTextInput();
    }
}