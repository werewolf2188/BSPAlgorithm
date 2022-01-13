//
//  AbsoluteMap.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 1/30/21.
//

#include <iostream>
#include <cmath>
#include "AbsoluteMap.h"
#include "../Classes/Structs.h"
#include "../Classes/Graphics.h"

AbsoluteMapSprite::AbsoluteMapSprite(Player player, Wall wall):
player(player),
wall(wall),
boundaries({ { 100, 100 }, {200, 300} }, BLUE)
{ }

bool AbsoluteMapSprite::onKeyPress(const Key& key) {
    return handleKeyboard(player, key);
}

void AbsoluteMapSprite::onRender(Graphics *g) {
    boundaries.onRender(g);
    // Draw wall
    g->drawLine({
        wall.origin.x + boundaries.getRect().position.x,
        wall.origin.y + boundaries.getRect().position.y
    }, {
        wall.destination.x + boundaries.getRect().position.x,
        wall.destination.y + boundaries.getRect().position.y
    }, MAROON);

    // Draw player
    int length = 10;
//    std::cout << player;
    Point p1 = {
        player.position.x + boundaries.getRect().position.x,
        player.position.y + boundaries.getRect().position.y
    };
    Point p2 = {
        (int)(((double)(player.position.x + boundaries.getRect().position.x)) + (cos(player.angle) * length)),
        (int)(((double)(player.position.y + boundaries.getRect().position.y)) + (sin(player.angle) * length))
    };
//    std::cout<< "origin: " << p1 << ", destination: " << p2 << std::endl;
    g->drawLine(p1, p2, PURPLE);
    g->drawPoint(p1, BLACK);
}
