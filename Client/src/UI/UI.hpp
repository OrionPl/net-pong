#pragma once

class UI; // DO NOT REMOVE (Breaks all UI elements due to UI not being defined)

#ifndef UI_H_
#define UI_H_

#include <vector>
#include <SDL2/SDL.h>

#include "UIElement.hpp" // Not needed i guess?
//#include "Text.hpp"
#include "Button.hpp"

//For different game states (Menu, In-Game) create different UI-s
class UI {
public:
    UI(SDL_Renderer* _renderer);

    void Draw();

    template<typename T>
    void AddUIElement(T* element); // Add templates to UI.cpp when adding new types of UI elements

    //template<typename T>
    //bool RemoveUIElement(std::string name); <--TODO // Returns true if the element was removed;

    SDL_Renderer* GetRenderer() { return renderer; };
    void SetRenderer(SDL_Renderer* _renderer) { renderer = _renderer; };

private:
    SDL_Renderer* renderer;
    //std::vector<Button*> buttons;
};
#endif