#include "Logic.hpp"

Logic::Logic() {
    window_length = 500;

    ball.x = ball.y = ball.l = ball.xv = ball.yv = 100;

    paddle_width = 30;
    paddle_height = 50;
    paddle_vy = 1000;
    p1.x = p1.y = p2.x = p2.y = -500;
}

void Logic::NewPlayer() {
    p1.x = p1.y = 10;
}

void Logic::Update() {
    clock.tick();

    UpdateBall();
    UpdatePaddles();

    network_msg = "$" + std::to_string(p1.x) + "," + std::to_string(p1.y);
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
    if (player == 1) {
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