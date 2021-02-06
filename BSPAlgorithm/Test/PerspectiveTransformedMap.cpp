//
//  PerspectiveTransformedMap.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 2/3/21.
//

#include "PerspectiveTransformedMap.h"

int cross(double x1, double y1, double x2, double y2) {
    return x1 * y2 - y1 * x2;
}

void intersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double& x, double& y) {
    x = cross(x1,y1, x2,y2);
    y = cross(x3,y3, x4,y4);
    int det = cross(x1-x2, y1-y2, x3-x4, y3-y4);
    x = cross(x, x1-x2, y, x3-x4) / det;
    y = cross(x, y1-y2, y, y3-y4) / det;
}

PerspectiveTransformedMapSprite::PerspectiveTransformedMapSprite(Player player, Wall wall):
player(player),
wall(wall),
boundaries({ { 600, 100 }, {200, 300} }, DARKGREEN),
originalPosition(player.position)
{ }

bool PerspectiveTransformedMapSprite::onKeyPress(const Key& key) {
    return handleKeyboard(player, key);
}

void PerspectiveTransformedMapSprite::onRender(Graphics *g) {
    boundaries.onRender(g);
    // Draw wall
    
    double tx1 = wall.origin.x - player.position.x;
    double ty1 = wall.origin.y - player.position.y;
    double tx2 = wall.destination.x - player.position.x;
    double ty2 = wall.destination.y - player.position.y;
    
    double tz1 = tx1 * cos(player.angle) + ty1 * sin(player.angle);
    double tz2 = tx2 * cos(player.angle) + ty2 * sin(player.angle);
    tx1 = tx1 * sin(player.angle) - ty1 * cos(player.angle);
    tx2 = tx2 * sin(player.angle) - ty2 * cos(player.angle);
    
    if (tz1 > 0 || tz2 > 0) {
        double ix1 = 0, iz1 = 0;
        double ix2 = 0, iz2 = 0;
        // What's up with these magic numbers
        intersect(tx1, tz1, tx2, tz2, -0.0001, 0.0001, -20, 5, ix1, iz1);
        intersect(tx1, tz1, tx2, tz2,  0.0001, 0.0001,  20, 5, ix2, iz2);

        if (tz1 <= 0) {
            if (iz1 > 0) {
                tx1 = ix1;
                tz1 = iz1;
            } else {
                tx1 = ix2;
                tz1 = iz2;
            }
        }
        if (tz2 <= 0) {
            if (iz1 > 0) {
                tx2 = ix1;
                tz2 = iz1;
            } else {
                tx2 = ix2;
                tz2 = iz2;
            }
        }
        // What does the 16 mean?
        double x1 = -tx1 * 16 / tz1;
        double y1a = -player.position.x / tz1;
        double y1b = player.position.x / tz1;
        double x2 = -tx2 * 16 / tz2;
        double y2a = -player.position.x / tz2;
        double y2b = player.position.x / tz2;
        
        Point w1 {
            originalPosition.x + (int)round(x1) + boundaries.getRect().position.x,
            originalPosition.x + (int)round(y1a) + boundaries.getRect().position.y,
        };
        Point w2 {
            originalPosition.x + (int)round(x1) + boundaries.getRect().position.x,
            originalPosition.x + (int)round(y1b) + boundaries.getRect().position.y,
        };
        Point w3 {
            originalPosition.x + (int)round(x2) + boundaries.getRect().position.x,
            originalPosition.x + (int)round(y2a) + boundaries.getRect().position.y,
        };
        Point w4 {
            originalPosition.x + (int)round(x2) + boundaries.getRect().position.x,
            originalPosition.x + (int)round(y2b) + boundaries.getRect().position.y,
        };
        // To paint the the full wall
//        for (double x = round(std::min(x1, x2)); x < round(std::max(x1, x2)); x++) {
//            double ya = y1a + (x - x1) * round(y2a - y1a) / (x2 - x1);
//            double yb = y1b + (x - x1) * round(y2b - y1b) / (x2 - x1);
//
//            Point wa {
//                originalPosition.x + (int)round(x) + boundaries.getRect().position.x,
//                originalPosition.x + (int)round(ya) + boundaries.getRect().position.y,
//            };
//            Point wb {
//                originalPosition.x + (int)round(x) + boundaries.getRect().position.x,
//                originalPosition.x + (int)round(yb) + boundaries.getRect().position.y,
//            };
//            g->drawLine(wa, wb, BLACK); // CENTER
//        }
        g->drawLine(w1, w3, PURPLE); // TOP
        g->drawLine(w2, w4, PURPLE); // BOTTOM
        g->drawLine(w1, w2, OLIVE); // LEFT
        g->drawLine(w3, w4, OLIVE); // RIGHT
    }
}
