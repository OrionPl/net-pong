#include "Ball.hpp"

Ball::Ball(int window_length) {
    m_window_length = window_length;
    m_xv = m_initial_xv = 100;
    m_yv = m_initial_yv = 100;
    m_x = m_rect.x = 150;
    m_y = m_rect.y = 50;
    m_rect.w = 50;
    m_rect.h = 50;
}

void Ball::Draw(SDL_Renderer* renderer) {
    SDL_RenderFillRect(renderer, &m_rect);
}

void Ball::Update(double dt, Score* score) {
    m_old_x = m_x;
    m_old_y = m_y;
    m_yv += m_yv < 0 ? -30 * dt: 30 * dt;
    m_xv += m_xv < 0 ? -30 * dt: 30 * dt;
    m_x += m_xv * dt;
    m_y += m_yv * dt;

    if (m_x + m_rect.w + 150 < 0 || m_x - 150 > m_window_length) {
        if (m_x < 0)
            score->p1();
        else
            score->p2();

        m_x = m_window_length / 2 - m_rect.w / 2;
        m_y = m_window_length / 2 - m_rect.h / 2;
        m_xv *= -1;
        m_yv = m_initial_yv;
        m_xv = m_initial_xv;
    }
    else if (m_y < 0) {
        m_y = 0;
        m_yv *= -1;
    }
    else if (m_y + m_rect.h > m_window_length) {
        m_y = m_window_length - m_rect.h;
        m_yv *= -1;
    }

    m_rect.x = m_x;
    m_rect.y = m_y;

}

void Ball::ReactToPaddle(float x, float y, int w, int h) {
    if (AABB(x, y, w, h, m_x, m_y, m_rect.w, m_rect.h)) {
        if (m_old_x > x + w || m_old_x + m_rect.w < x) {
            m_xv *= -1;
        }
        if (m_old_y > y + h || m_old_y + m_rect.h < y) {
            m_yv *= -1;
        }
    }
}

bool Ball::AABB(float x, float y, int w, int h, float x2, float y2, int w2, int h2) {
    return x + w > x2 && x < x2 + w2 && y + h > y2 && y < y2 + h2;
}