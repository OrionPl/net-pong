#include "Window.hpp"

Window::Window() {
    window = SDL_CreateWindow("pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, g_data.w, g_data.h, SDL_WINDOW_SHOWN);
    SDL_UpdateWindowSurface(window);
    g_data.rdr = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    icon = IMG_Load("assets/icon.png");
    if (!icon) SDL_Log("icon.png not loaded");
    SDL_SetWindowIcon(window, icon);
}

void Window::Clear() {
    SDL_SetRenderDrawColor(g_data.rdr, 0, 0, 0, 0);
    SDL_RenderClear(g_data.rdr);
    SDL_SetRenderDrawColor(g_data.rdr, 255, 255, 255, 255);
}

void Window::Shutdown() {
    SDL_Log("Shutting down window");
    SDL_FreeSurface(icon);
    SDL_DestroyRenderer(g_data.rdr);
    SDL_DestroyWindow(window);
}