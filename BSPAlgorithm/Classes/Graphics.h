//
//  Graphics.h
//  BSPAlgorithm
//
//  Created by Enrique on 4/28/21.
//

#ifndef Graphics_h
#define Graphics_h

#include "Structs.h"

class Graphics {
public:
    virtual void drawPoint(Point p, Color c) = 0;
    virtual void drawLine(Point from, Point to, Color c) = 0;
    virtual void drawRect(Rect r, Color c) = 0;
    virtual void drawCircle(Point center, int radius, Color color) = 0;
    virtual void drawDisk(Point center, int radius, Color color) = 0;
    virtual void clear() = 0;
    virtual void update() = 0;
public:
    virtual Size getDrawableSize() const = 0;
};
#endif /* Graphics_h */
