#include "Score.hpp"

Score::Score(SDL_Renderer* renderer) {
    m_renderer = renderer;

    m_score_1 = m_score_2 = -1;
    p1();
    p2();

    m_score_1_rect.x = 150;
    m_score_1_rect.y = 150;
    m_score_2_rect.x = 50;
    m_score_2_rect.y = 50;


    SDL_QueryTexture(m_texture_1, NULL, NULL, &m_score_1_rect.w, &m_score_1_rect.h);
    SDL_QueryTexture(m_texture_1, NULL, NULL, &m_score_2_rect.w, &m_score_2_rect.h);
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