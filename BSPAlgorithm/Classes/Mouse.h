//
//  Mouse.h
//  BSPAlgorithm
//
//  Created by Enrique on 1/27/21.
//

#ifndef Mouse_h
#define Mouse_h
#include "Structs.h"

class MouseListener {
public:
    virtual bool onMouseMove(Point p) { return false; }
    virtual bool onRelativeMouse(Point p) { return false; }
};
#endif /* Mouse_h */
