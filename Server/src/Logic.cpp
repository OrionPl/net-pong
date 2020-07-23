#include "Logic.hpp"

Logic::Logic() {
    window_length = 500;

    paddle_vy = 1000;
    p1.x = p1.y = p2.x = p2.y = -500;
    ball.x = ball.y = ball.l = ball.xv = ball.yv = 100;
}

void Logic::NewPlayer() {
    p1.x = p1.y = 10;
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

    MovePaddles();

    network_msg = "$" + std::to_string(p1.x) + "," + std::to_string(p1.y);
    //std:: cout << network_msg << " | clock: " << clock.dt << " | vel = " << float(paddle_vy * clock.dt) << "down=" << p1Down << "up=" << p1Up << std::endl;
}

void Logic::TakeInput(int player, std::string input) {
    if (player == 1) {
        if (input == "v") {
            p1.direction = 1;
        } else if (input == "^") {
            p1.direction = -1;
        } else {
            p1.direction = 0;
        }
    } else {
        if (input == "v") {
            p2.direction = 1;
        } else if (input == "^") {
            p2.direction == -1;
        } else {
            p2.direction = 0;
        }
    }
}

void Logic::MovePaddles() {
    p1.y += paddle_vy * p1.direction * clock.dt;
    p2.y += paddle_vy * p2.direction * clock.dt;
}

std::string Logic::GetNetworkMsg() {
    return network_msg;
}

// checks if the x values have been set, i.e. whether a player has connected
bool Logic::GameFull() {
    return p1.x == -1 || p2.x == -1;
}