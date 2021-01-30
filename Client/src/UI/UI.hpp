#pragma once

class UI; // DO NOT REMOVE (Breaks all UI elements due to UI not being defined)

#include <vector>
#include <SDL2/SDL.h>
#include "Button.hpp"
#include "Text.hpp"

//For different game states (Menu, In-Game) create different UI-s
class UI {
public:
    UI(SDL_Renderer* _renderer);

    void Draw();

    template<typename T>
    void AddUIElement(T* element); // Add templates to UI.cpp when adding new types of UI elements

    //template<typename T>
    //bool RemoveUIElement(std::string name); <--TODO // Returns true if the element was removed;

    template<typename T>
    T GetUIElement(std::string name);

    SDL_Renderer* GetRenderer() { return renderer; };
    void SetRenderer(SDL_Renderer* _renderer) { renderer = _renderer; };

private:
    SDL_Renderer* renderer;
    std::vector<Button*> buttons;
    std::vector<Text*> texts;
};