#include "Logic.hpp"

Logic::Logic() {
    window_length = 500;

    ball.x = ball.y = ball.l = ball.xv = ball.yv = 100;

    paddle_width = 30;
    paddle_height = 50;
    paddle_vy = 1000;
    default_offscreen_v = -500;
    p1.x = p1.y = p2.x = p2.y = default_offscreen_v; // default off-screen value
}

int Logic::NewPlayer_GetIndex() {
    if (p1.x == default_offscreen_v)
        p1.x = p1.y = 10;
    else
        p2.x= window_length - paddle_width;
        p2.y = 10;

    return p2.x != default_offscreen_v; // if this is true, that means we have only set the first player, otherwise we have set both players. The bools evaluate to the index because we only ever get 2 players at once.
}

void Logic::RemovePlayer(int p_index) {
    if (p_index) {
        p2.x = p2.y = default_offscreen_v;
    } else {
        p1.x = p1.y = default_offscreen_v;
    }
}

void Logic::Update() {
    clock.tick();

    UpdateBall();
    UpdatePaddles();

    network_msg = "$" + std::to_string(p1.x) + "," + std::to_string(p1.y) + "," + std::to_string(p2.x) + "," + std::to_string(p2.y);
}

void Logic::UpdateBall() {
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
    p1.y += paddle_vy * p1.direction * clock.dt;
    p2.y += paddle_vy * p2.direction * clock.dt;

    if (p1.y < 0)
        p1.y = 0;
    if (p2.y < 0)
        p2.y = 0;
    if (p1.y + paddle_height > window_length)
        p1.y = window_length - paddle_height;
    if (p2.y + paddle_height > window_length)
        p2.y = window_length - paddle_height;
}

void Logic::TakeInput(int player, std::string input) {
    if (!player) { // -1 because player *** 1 *** has index *** 0 ***
        p1.direction = std::stoi(input);
    } else {
        p2.direction = std::stoi(input);
    }
}

std::string Logic::GetNetworkMsg() {
    return network_msg;
}

// checks if the x values have been set, i.e. whether a player has connected
bool Logic::GameFull() {
    return p1.x == -1 || p2.x == -1;
}