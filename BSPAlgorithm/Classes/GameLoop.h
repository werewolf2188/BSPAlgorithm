//
//  GameLoop.hpp
//  BSPAlgorithm
//
//  Created by Enrique on 1/25/21.
//

#ifndef GameLoop_hpp
#define GameLoop_hpp

#include <stdio.h>
#include "Graphics.h"
#include "Structs.h"
#include "Sprite.h"

class GameLoop {
private:
    Graphics* graphics;
    Sprite* sprite;
public:
    GameLoop();
    ~GameLoop();
    void addSprites(Sprite *sprite);
    void start(Graphics* graphics);
};
#endif /* GameLoop_hpp */
