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
#include "GameLoop.h"

class UserInputGameLoop: public GameLoop {
private:
    Graphics* graphics;
    std::vector<Sprite*> sprites;
public:
    UserInputGameLoop();
    ~UserInputGameLoop();
    void addSprites(Sprite *sprite);
    void start(Graphics* graphics, UI* ui);
};
#endif /* GameLoop_hpp */
