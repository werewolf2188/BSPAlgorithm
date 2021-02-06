//
//  AbsoluteMap.hpp
//  BSPAlgorithm
//
//  Created by Enrique on 1/30/21.
//

#ifndef AbsoluteMap_hpp
#define AbsoluteMap_hpp

#include "Boundaries.h"
#include "Player.h"
#include "Wall.h"
#include "../Classes/Sprite.h"
#include "../Classes/Keyboard.h"

class Graphics;

class AbsoluteMapSprite: public Sprite, public KeyListener {
private:
    Player player;
    BoundariesSprite boundaries;
    Wall wall;
public:
    AbsoluteMapSprite(Player player, Wall wall);
    bool onKeyPress(const Key& key);
    void onRender(Graphics *g);
};

#endif /* AbsoluteMap_hpp */
