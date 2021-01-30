//
//  Player.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 1/30/21.
//

#include "Player.h"
#include <cmath>

double degToRad(double deg) {
    return deg * M_PI / 180.0;
}

int ceilOrFloor(double calculation, double angle) {
    if (angle < 0) return (int)floor(calculation);
    else return (int)ceil(calculation);
}

int degreesToAdd = 18;
int fullCircle = 360;

bool handleKeyboard(Player &player, const Key& key) {
    bool handle = false;
    if (key == SDL_SCANCODE_W) {
        double x = ((double)player.position.x) + (cos(player.angle));
        double y = ((double)player.position.y) + (sin(player.angle));
        player.position.x = (int)ceilOrFloor(x, cos(player.angle));
        player.position.y = (int)ceilOrFloor(y, sin(player.angle));
        handle = true;
    } else if (key == SDL_SCANCODE_S) {
        double x = ((double)player.position.x) - (cos(player.angle));
        double y = ((double)player.position.y) - (sin(player.angle));
        player.position.x = (int)ceilOrFloor(x, -cos(player.angle));
        player.position.y = (int)ceilOrFloor(y, -sin(player.angle));
        handle = true;
    } else if (key == SDL_SCANCODE_A) {
        player.angle -= degToRad(degreesToAdd);
        if (player.angle < -degToRad(fullCircle)) {
            player.angle = 0;
        }
        handle = true;
    } else if (key == SDL_SCANCODE_D) {
        player.angle += degToRad(degreesToAdd);
        if (player.angle == degToRad(fullCircle)) {
            player.angle = 0;
        }
        handle = true;
    }
    return handle;
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Player is in location:" << player.position << " and its angle is " << player.angle << std::endl;
    return os;
}
