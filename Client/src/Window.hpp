#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Window {
public:
    Window();
    SDL_Renderer* GetRenderer();
    int GetWindowLength();
    void Shutdown();
private:
    int m_window_length;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Surface* m_icon;
};