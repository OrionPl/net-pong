#include "Logic.hpp"

Logic::Logic() {
    p1.x = p1.y = p2.x = p2.y = -1;
    ball.x = ball.y = 100;
}

void Logic::Update() {
    clock.tick();
}

void Logic::TakeInput(int player, std::string input) {
    if (player == 1) {
        if (input == "v") {
            p1.x += paddle_vy * dt;
        } else {
            p1.x -= paddle_vy * dt;
        }
    } else {
        if (input == "v") {
            p2.x += paddle_vy * dt;
        } else {
            p2.x -= paddle_vy * dt;
        }
    }
}

// checks if the x values have been set, i.e. whether a player has connected
bool GameFull() {
    return p1.x == -1 || p2.x == -1;
}