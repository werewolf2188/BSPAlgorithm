//
//  TransformedMap.hpp
//  BSPAlgorithm
//
//  Created by Enrique on 1/31/21.
//

#ifndef TransformedMap_hpp
#define TransformedMap_hpp

#include "Boundaries.h"
#include "Player.h"
#include "Wall.h"
#include "../Classes/Sprite.h"
#include "../Classes/Keyboard.h"

class Graphics;

class TransformedMapSprite: public Sprite, public KeyListener {
private:
    Player player;
    Point originalPosition;
    BoundariesSprite boundaries;
    Wall wall;
public:
    TransformedMapSprite(Player player, Wall wall);
    bool onKeyPress(const Key& key);
    void onRender(Graphics *g);
};

#endif /* TransformedMap_hpp */
