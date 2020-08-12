#include "Score.hpp"

Score::Score() {

    score_1 = score_2 = -1;
    p1();
    p2();

    SDL_QueryTexture(texture_1, NULL, NULL, &score_1_rect.w, &score_1_rect.h);
    SDL_QueryTexture(texture_1, NULL, NULL, &score_2_rect.w, &score_2_rect.h);

    score_1_rect.x = global_window_data.w / 4 - score_1_rect.w / 2;
    score_1_rect.y = global_window_data.h / 4 - score_1_rect.h / 2;
    score_2_rect.x = global_window_data.w / 4 * 3 - score_2_rect.w / 2;
    score_2_rect.y = global_window_data.h / 4 - score_2_rect.h / 2;
}

void Score::Draw() {
	SDL_RenderCopy(global_window_data.rdr, texture_1, NULL, &score_1_rect);
    SDL_RenderCopy(global_window_data.rdr, texture_2, NULL, &score_2_rect);
}

void Score::p1() {
    score_1++;
    texture_1 = Text::CreateTexture(global_window_data.rdr, std::to_string(score_1));
}

void Score::p2() {
    score_2++;
    texture_2 = Text::CreateTexture(global_window_data.rdr, std::to_string(score_2));
}

void Score::DestroyTextures() {
    SDL_DestroyTexture(texture_1);
    SDL_DestroyTexture(texture_2);
}