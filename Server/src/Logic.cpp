#include "Logic.hpp"

Logic::Logic() {
    window_length = 500;

    p1.x = p1.y = p2.x = p2.y = -500;
    ball.x = ball.y = ball.l = ball.xv = ball.yv = 100;
}

void Logic::NewPlayer() {
    if (p1.x == -1) {
        p1.x = p1.y = 10;
    }
}

void Logic::Update() {
    clock.tick();

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



    network_msg = "$" + std::to_string(0) + "," + std::to_string(0);
}

void Logic::TakeInput(int player, std::string input) {
    if (player == 1) {
        if (input == "v") {
            std::cout << "player 1: pressing down" << std::endl;
            p1.y += paddle_vy * clock.dt;
        } else {
            std::cout << "player 1: pressing up" << std::endl;
            p1.y -= paddle_vy * clock.dt;
        }
    } else {
        if (input == "v") {
            p2.y += paddle_vy * clock.dt;
        } else {
            p2.y -= paddle_vy * clock.dt;
        }
    }
}

std::string Logic::GetNetworkMsg() {
    return network_msg;
}

// checks if the x values have been set, i.e. whether a player has connected
bool Logic::GameFull() {
    return p1.x == -1 || p2.x == -1;
}