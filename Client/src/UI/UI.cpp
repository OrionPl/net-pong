#include "UI.hpp"

UI::UI(SDL_Renderer* _renderer) {
    renderer = _renderer;
}

template<>
void UI::AddUIElement(Button* element) {
    buttons.push_back(element);
}

// template<>
// bool UI::RemoveUIElement(std::string name) {
//     for (int i : buttons) {
//         if (buttons[i].name == name)
//             buttons.erase(buttons.begin() + i);
//     }
// }