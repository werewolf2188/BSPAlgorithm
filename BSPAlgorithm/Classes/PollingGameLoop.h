//
//  PollingGameLoop.hpp
//  BSPAlgorithm
//
//  Created by Enrique on 4/30/21.
//

#ifndef PollingGameLoop_hpp
#define PollingGameLoop_hpp

#include <stdio.h>
#include "Graphics.h"
#include "Structs.h"
#include "Sprite.h"
#include "UI.h"
#include <vector>
#include "GameLoop.h"

class PollingGameLoop: public GameLoop {
private:
    Graphics* graphics;
    std::vector<Sprite*> sprites;
public:
    PollingGameLoop();
    ~PollingGameLoop();
    void addSprites(Sprite *sprite);
    void start(Graphics* graphics, UI* ui);
};

#endif /* PollingGameLoop_hpp */
