//
//  PerspectiveTransformedMap.hpp
//  BSPAlgorithm
//
//  Created by Enrique on 2/3/21.
//

#ifndef PerspectiveTransformedMap_hpp
#define PerspectiveTransformedMap_hpp

#include "Boundaries.h"
#include "Player.h"
#include "Wall.h"
#include "../Classes/Sprite.h"
#include "../Classes/Keyboard.h"

class Graphics;

class PerspectiveTransformedMapSprite: public Sprite, public KeyListener {
private:
    Player player;
    Point originalPosition;
    BoundariesSprite boundaries;
    Wall wall;
public:
    PerspectiveTransformedMapSprite(Player player, Wall wall);
    bool onKeyPress(const Key& key);
    void onRender(Graphics *g);
};

#endif /* PerspectiveTransformedMap_hpp */
