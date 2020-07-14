#include "Paddles.hpp"

Paddles::Paddles(int window_length) {
    m_window_length = window_length;

    m_paddle1.score = m_paddle2.score = 0;
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

void Paddles::Update(double dt, const Uint8* keys_down, Ball* ball) {
    if (keys_down[SDL_SCANCODE_UP]) {
        m_paddle2.y -= m_yv * dt;
    } else if (keys_down[SDL_SCANCODE_DOWN]) {
        m_paddle2.y += m_yv * dt;
    }

    if (keys_down[SDL_SCANCODE_W]) {
        m_paddle1.y -= m_yv * dt;
    } else if (keys_down[SDL_SCANCODE_S]) {
        m_paddle1.y += m_yv * dt;
    }

    if (m_paddle1.y < 0)
        m_paddle1.y = 0;
    if (m_paddle2.y < 0)
        m_paddle2.y = 0;
    if (m_paddle1.y + m_rect.h > m_window_length)
        m_paddle1.y = m_window_length - m_rect.h;
    if (m_paddle2.y + m_rect.h > m_window_length)
        m_paddle2.y = m_window_length - m_rect.h;

    ball->ReactToPaddle(m_paddle1.x, m_paddle1.y, m_rect.w, m_rect.h);
    ball->ReactToPaddle(m_paddle2.x, m_paddle2.y, m_rect.w, m_rect.h);
}