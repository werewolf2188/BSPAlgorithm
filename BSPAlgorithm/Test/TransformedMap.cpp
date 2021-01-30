//
//  TransformedMap.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 1/31/21.
//

#include "TransformedMap.h"

TransformedMapSprite::TransformedMapSprite(Player player, Wall wall):
player(player),
wall(wall),
boundaries({ { 350, 100 }, {200, 300} }, RED),
originalPosition(player.position)
{ }

bool TransformedMapSprite::onKeyPress(const Key& key) {
    return handleKeyboard(player, key);
}

void TransformedMapSprite::onRender(Graphics *g) {
    boundaries.onRender(g);
    // Draw wall
    
    int tx1 = wall.origin.x - player.position.x;
    int ty1 = wall.origin.y - player.position.y;
    int tx2 = wall.destination.x - player.position.x;
    int ty2 = wall.destination.y - player.position.y;
    
    int tz1 = tx1 * cos(player.angle) + ty1 * sin(player.angle);
    int tz2 = tx2 * cos(player.angle) + ty2 * sin(player.angle);
    tx1 = tx1 * sin(player.angle) - ty1 * cos(player.angle);
    tx2 = tx2 * sin(player.angle) - ty2 * cos(player.angle);
    
    Point w1 {
        originalPosition.x - tx1 + boundaries.getRect().position.x,
        originalPosition.x - tz1 + boundaries.getRect().position.y,
    };
    Point w2 {
        originalPosition.x - tx2 + boundaries.getRect().position.x,
        originalPosition.x - tz2 + boundaries.getRect().position.y,
    };
    g->drawLine(w1, w2, OLIVE);
    
    // Draw player
    
    int length = 10;
    Point p1 = {
        originalPosition.x + boundaries.getRect().position.x,
        originalPosition.x + boundaries.getRect().position.y
    };
    Point p2 = {
        originalPosition.x + boundaries.getRect().position.x,
        originalPosition.x - length + boundaries.getRect().position.y
    };
    g->drawLine(p1, p2, TEAL);
    g->drawPoint(p1, BLACK);
}
