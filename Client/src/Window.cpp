#include "Window.hpp"

Window::Window() {
    m_window_length = 500;
    m_window = SDL_CreateWindow("pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_window_length, m_window_length, SDL_WINDOW_SHOWN);
    SDL_UpdateWindowSurface(m_window);

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
}

SDL_Renderer* Window::GetRenderer() {
    return m_renderer;
}

int Window::GetWindowLength() {
    return m_window_length;
}

void Window::Shutdown() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}