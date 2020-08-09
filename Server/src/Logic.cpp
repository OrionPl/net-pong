#include "Logic.hpp"

Logic::Logic() {
    window_length = 500;

    ball.x = ball.y = ball.l = 100;
    ball.xv = ball.yv = 1000;

    paddle_width = 30;
    paddle_height = 50;
    paddle_vy = 1000;
    default_offscreen_v = -500;
    p1.x = p1.y = p2.x = p2.y = default_offscreen_v;
    game_paused = true;
}

int Logic::NewPlayer_GetIndex() {
    if (p1.x == default_offscreen_v) {
        p1.x = p1.y = 10;
        return 0;
    }
    else {
        p2.x= window_length - paddle_width - 10;
        p2.y = 10;
        return 1;
    }

    return -1; // if this is true, that means we have only set the first player, otherwise we have set both players. The bools evaluate to the index because we only ever get 2 players at once.
}

void Logic::SetPlayerName(int p_index, std::string name) {
    if (p_index) { // if the index is 1
        p2.name = name;
    } else {
        p1.name = name;
    }
}

void Logic::RemovePlayer(int p_index) {
    if (p_index) { // if the index is 1
        p2.x = p2.y = default_offscreen_v;
        p2.name = "";
    } else {
        p1.x = p1.y = default_offscreen_v;
        p1.name = "";
    }
}

void Logic::Update() {
    clock.tick();

    if (!game_paused) {
        UpdateBall();
        UpdatePaddles();
    }

    network_msg = "$" + std::to_string(p1.x) + "," + std::to_string(p1.y) + "," + std::to_string(p2.x) + "," + std::to_string(p2.y) + "," + std::to_string(ball.x) + "," + std::to_string(ball.y);
}
#include "Utilities/Print.h"
void Logic::UpdateBall() {
    PRINT std::to_string(p1.x) + "," + std::to_string(p1.y) + "," + std::to_string(p2.x) + "," + std::to_string(p2.y) + "," + std::to_string(ball.x) + "," + std::to_string(ball.y) + "," + std::to_string(game_paused) + "," + std::to_string(clock.dt) + "\n";
    ball.x += ball.xv * clock.dt;
    ball.y += ball.yv * clock.dt;
    if (ball.y < 0) {
        ball.y = 0;
        ball.yv *= -1;
    }
    else if (ball.y + ball.l > window_length) {
        ball.y = window_length - ball.l;
        ball.yv *= -1;
    }
}

void Logic::UpdatePaddles() {

    if (p1.x != default_offscreen_v) { // checking whether the positions have actually been initialised (i.e. whether there's a player)

        p1.y += paddle_vy * p1.direction * clock.dt;
        if (p1.y < 0) p1.y = 0;
        if (p1.y + paddle_height > window_length) p1.y = window_length - paddle_height;

    }

    if (p2.x != default_offscreen_v) {

        p2.y += paddle_vy * p2.direction * clock.dt;
        if (p2.y < 0) p2.y = 0;
        if (p2.y + paddle_height > window_length) p2.y = window_length - paddle_height;

    }
}

void Logic::TakeInput(int player, std::string input) {
    if (player) p2.direction = std::stoi(input); // if player index is 1, then it means player 2, because we have player indexes [0, 1]
    else p1.direction = std::stoi(input);
}

void Logic::PauseGame() {
    game_paused = true;
}

void Logic::UnpauseGame() {
    game_paused = false; // <<------------------------ TODO COUNTDOWN / BUTTON TO START GAME
}

std::string Logic::GetNetworkMsg() { return network_msg; }