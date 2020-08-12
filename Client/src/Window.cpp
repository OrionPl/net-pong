#include "Window.hpp"

Window::Window() {
    window = SDL_CreateWindow("pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, global_window_data.w, global_window_data.h, SDL_WINDOW_SHOWN);
    SDL_UpdateWindowSurface(window);
    global_window_data.rdr = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    icon = IMG_Load("assets/icon.png");
    if (!icon) SDL_Log("icon.png not loaded");
    SDL_SetWindowIcon(window, icon);
}

void Window::Clear() {
    SDL_SetRenderDrawColor(global_window_data.rdr, 0, 0, 0, 0);
    SDL_RenderClear(global_window_data.rdr);
    SDL_SetRenderDrawColor(global_window_data.rdr, 255, 255, 255, 255);
}

void Window::Shutdown() {
    SDL_Log("Shutting down window");
    SDL_FreeSurface(icon);
    SDL_DestroyRenderer(global_window_data.rdr);
    SDL_DestroyWindow(window);
    SDL_Quit();
}