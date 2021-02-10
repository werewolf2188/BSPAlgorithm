//
//  Player.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 2/8/21.
//

#include "Player.h"

Player::Player(Vector2 pos, float angle, unsigned int sector):
position({ pos.x, pos.y, 0 }),
velocity({ 0, 0, 0 }),
angle(angle),
sector(sector) { }
