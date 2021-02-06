//
//  Boundaries.hpp
//  BSPAlgorithm
//
//  Created by Enrique on 1/30/21.
//

#ifndef Boundaries_hpp
#define Boundaries_hpp

#include <stdio.h>
#include "../Classes/Sprite.h"

class Graphics;
struct Rect;
struct Color;

// Example of class with sprite, key listener and mouse listener
class BoundariesSprite: public Sprite {
private:
    Rect r;
    Color color;
public:
    BoundariesSprite(Rect r, Color color);
    void onRender(Graphics *g);
    Rect getRect();
};

#endif /* Boundaries_hpp */
