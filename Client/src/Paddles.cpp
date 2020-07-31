#include "Paddles.hpp"

Paddles::Paddles(int window_length) {
    m_window_length = window_length;

    m_rect.w = 30;
    m_rect.h = 50;
    m_yv = 500;
    m_paddle1.x = 10;
    m_paddle2.x = window_length - 10 - m_rect.w;
    m_paddle1.y = m_paddle2.y = 50;
}

void Paddles::Draw(SDL_Renderer* renderer) {
    m_rect.x = m_paddle1.x;
    m_rect.y = m_paddle1.y;
    SDL_RenderDrawRect(renderer, &m_rect);

    m_rect.x = m_paddle2.x;
    m_rect.y = m_paddle2.y;
    SDL_RenderDrawRect(renderer, &m_rect);
}

void Paddles::SetPaddle(int index, float x, float y) {
    if (!index) {
        m_paddle1.x = x;
        m_paddle1.y = y;
    } else {
        m_paddle2.x = x;
        m_paddle1.y = y;
    }
}