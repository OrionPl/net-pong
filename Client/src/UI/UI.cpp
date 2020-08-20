#include "UI.hpp"

UI::UI(SDL_Renderer* _renderer) {
    renderer = _renderer;
}

void UI::Draw() {
    for (auto btn : buttons)
        btn->Draw();
    for (auto txt : texts)
        txt->Draw();
}

template<>
void UI::AddUIElement(Button* element) {
    buttons.push_back(element);
}

template<>
void UI::AddUIElement(Text* element) {
    texts.push_back(element);
}

// template<>
// bool UI::RemoveUIElement(std::string name) {
//     for (int i : buttons) {
//         if (buttons[i].name == name)
//             buttons.erase(buttons.begin() + i);
//     }
// }

template<>
Button* UI::GetUIElement(std::string name) {
    for (auto a : buttons)
        if (a->GetName() == name)
            return a;
}

template<>
Text* UI::GetUIElement(std::string name) {
    for (auto a : texts)
        if (a->GetName() == name)
            return a;
}