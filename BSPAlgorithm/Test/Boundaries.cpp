//
//  Boundaries.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 1/30/21.
//

#include "Boundaries.h"
#include "../Classes/Sprite.h"
#include "../Classes/Structs.h"
#include "../Classes/Graphics.h"

BoundariesSprite::BoundariesSprite(Rect r, Color color): r(r), color(color) { }

void BoundariesSprite::onRender(Graphics *g) {
    g->drawRect(r, color);
}

Rect BoundariesSprite::getRect() {
    return r;
}
