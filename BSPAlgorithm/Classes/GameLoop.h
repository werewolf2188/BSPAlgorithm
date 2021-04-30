//
//  GameLoop.h
//  BSPAlgorithm
//
//  Created by Enrique on 4/30/21.
//

#ifndef GameLoop_h
#define GameLoop_h

#include <stdio.h>
#include "Graphics.h"
#include "Structs.h"
#include "Sprite.h"
#include "UI.h"
#include <vector>

class GameLoop {
public:
    virtual void addSprites(Sprite *sprite) = 0;
    virtual void start(Graphics* graphics, UI* ui) = 0;
};

#endif /* GameLoop_h */
