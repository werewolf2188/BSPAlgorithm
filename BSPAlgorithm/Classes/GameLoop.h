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
#include "UI.h"
#include <vector>

class GameLoop {
private:
    Graphics* graphics;
    std::vector<Sprite*> sprites;
public:
    GameLoop();
    ~GameLoop();
    void addSprites(Sprite *sprite);
    void start(Graphics* graphics, UI* ui);
};
#endif /* GameLoop_hpp */
