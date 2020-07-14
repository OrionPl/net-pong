#include "Score.hpp"

Score::Score(SDL_Renderer* renderer) {

    m_font = TTF_OpenFont("font.ttf", 15);

    m_score_1 = 0;
    m_score_2 = 0;

    m_score_1_rect.x = 150;
    m_score_1_rect.y = 150;
    m_score_2_rect.x = 50;
    m_score_2_rect.y = 50;

    m_color_white;
    m_color_white.r = m_color_white.g = m_color_white.b = m_color_white.a = 255;

    m_renderer = renderer;
	//Render text surface
	SDL_Surface* score1 = TTF_RenderText_Solid(m_font, "0", m_color_white);
    SDL_Surface* score2 = TTF_RenderText_Solid(m_font, "0", m_color_white);

    m_score_1_rect.w = score1->w;
    m_score_1_rect.h = score1->h;
    m_score_2_rect.w = score2->w;
    m_score_2_rect.h = score2->h;


    //Create texture from surface pixels
    m_texture_1 = SDL_CreateTextureFromSurface(m_renderer, score1);
    m_texture_2 = SDL_CreateTextureFromSurface(m_renderer, score2);
    //Get rid of old surface
    SDL_FreeSurface(score1);
    SDL_FreeSurface(score2);

}

void Score::Draw() {
	SDL_RenderCopy(m_renderer, m_texture_1, NULL, &m_score_1_rect);
    SDL_RenderCopy(m_renderer, m_texture_2, NULL, &m_score_2_rect);
}

void Score::p1() {
    m_score_1++;

    SDL_Surface* surface = TTF_RenderText_Solid(m_font, std::to_string(m_score_1).c_str(), m_color_white);
    m_texture_1 = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);
}

void Score::p2() {
    m_score_2++;

    SDL_Surface* surface = TTF_RenderText_Solid(m_font, std::to_string(m_score_2).c_str(), m_color_white);
    m_texture_2 = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);
}