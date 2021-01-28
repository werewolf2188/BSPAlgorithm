//
//  Sprite.h
//  BSPAlgorithm
//
//  Created by Enrique on 1/27/21.
//

#ifndef Sprite_h
#define Sprite_h
#include "Graphics.h"

class Sprite {
public:
    virtual void onRender(Graphics *g) = 0;
};

#endif /* Sprite_h */
