#include "Score.hpp"

Score::Score(SDL_Renderer* renderer, int _window_length) {
    m_renderer = renderer;
    window_length = _window_length;

    m_score_1 = m_score_2 = -1;
    p1();
    p2();

    SDL_QueryTexture(m_texture_1, NULL, NULL, &m_score_1_rect.w, &m_score_1_rect.h);
    SDL_QueryTexture(m_texture_1, NULL, NULL, &m_score_2_rect.w, &m_score_2_rect.h);

    m_score_1_rect.x = window_length / 4 - m_score_1_rect.w / 2;
    m_score_1_rect.y = window_length / 4 - m_score_1_rect.h / 2;
    m_score_2_rect.x = window_length / 4 * 3 - m_score_2_rect.w / 2;
    m_score_2_rect.y = window_length / 4 - m_score_2_rect.h / 2;
}

void Score::Draw() {
	SDL_RenderCopy(m_renderer, m_texture_1, NULL, &m_score_1_rect);
    SDL_RenderCopy(m_renderer, m_texture_2, NULL, &m_score_2_rect);
}

void Score::p1() {
    m_score_1++;
    m_texture_1 = Text::CreateTexture(m_renderer, std::to_string(m_score_1));
}

void Score::p2() {
    m_score_2++;
    m_texture_2 = Text::CreateTexture(m_renderer, std::to_string(m_score_2));
}

void Score::DestroyTextures() {
    SDL_DestroyTexture(m_texture_1);
    SDL_DestroyTexture(m_texture_2);
}