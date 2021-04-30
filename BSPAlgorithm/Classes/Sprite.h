//
//  Sprite.h
//  BSPAlgorithm
//
//  Created by Enrique on 1/27/21.
//

#ifndef Sprite_h
#define Sprite_h
#include "Graphics.h"
#include "UI.h"

class Sprite {
public:
    virtual void onRender(Graphics *g) = 0;
    virtual bool onUI(UI *ui) { return false; }
};

#endif /* Sprite_h */
