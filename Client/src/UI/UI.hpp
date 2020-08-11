#pragma once

#include <vector>
#include <SDL/SDL.h>

#include "UIElement.hpp"
#include "Text.hpp"
#include "Button.hpp"

//For different game states (Menu, In-Game) create different UI-s
class UI {
public:
    UI(SDL_Renderer* _renderer);

    void Draw();
    void AddUIElement(UIElement* element);

    template<typename T>
    bool RemoveUIElement(std::string name); // Returns true if the element was removed;

    SDL_Renderer* GetRenderer() { return renderer; };
    void SetRenderer(SDL_Renderer* _renderer) { renderer = _renderer; };

private:
    SDL_Renderer* renderer;

    private std::vector<UIElement*> ui_elements;
}