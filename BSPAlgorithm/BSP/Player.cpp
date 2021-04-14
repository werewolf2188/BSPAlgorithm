//
//  Player.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 2/8/21.
//

#include "Player.h"
#include <cmath>

Player::Player(Vector2 pos, float angle, unsigned int sector, float z):
position({ pos.x, pos.y, z }),
velocity({ 0, 0, 0 }),
angle(angle),
anglesin(0), // I'm not sure about the initialization
anglecos(0), // I'm not sure about the initialization
sector(sector) { }

Vector3 Player::getPosition() {
    return position;
}

void Player::setPosition(Vector3 position) {
    this->position = position;
}

Vector3 Player::getVelocity() {
    return velocity;
}

void Player::setVelocity(Vector3 velocity) {
    this->velocity = velocity;
}

float Player::getAngle() {
    return angle;
}

void Player::setAngle(float angle) {
    this->angle = angle;
}

float Player::getAnglesin() {
    return anglesin;
}

void Player::setAnglesin(float anglesin) {
    this->anglesin = anglesin;
}

float Player::getAnglecos() {
    return anglecos;
}

void Player::setAnglecos(float anglecos) {
    this->anglecos = anglecos;
}

unsigned int Player::getSector() {
    return sector;
}

void Player::setSector(unsigned int sector) {
    this->sector = sector;
}

float Player::getYaw() {
    return yaw;
}

void Player::setYaw(float yaw) {
    this->yaw = yaw;
}
