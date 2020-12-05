#include "Paddles.hpp"

Paddles::Paddles() {
    m_rect.w = 30;
    m_rect.h = 50;
    m_yv = 500;
    m_paddle1.x = 10;
    m_paddle2.x = g_data.w - 10 - m_rect.w;
    m_paddle1.y = m_paddle2.y = 50;
}

void Paddles::Draw() {
    m_rect.x = m_paddle1.x;
    m_rect.y = m_paddle1.y;
    SDL_RenderDrawRect(g_data.rdr, &m_rect);

    m_rect.x = m_paddle2.x;
    m_rect.y = m_paddle2.y;
    SDL_RenderDrawRect(g_data.rdr, &m_rect);
}

void Paddles::SetPaddles(float x1, float y1, float x2, float y2) {
    m_paddle1.x = x1;
    m_paddle1.y = y1;
    m_paddle2.x = x2;
    m_paddle2.y = y2;
}