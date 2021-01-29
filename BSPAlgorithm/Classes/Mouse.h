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
    virtual void onMouseMove(Point p) = 0;
};
#endif /* Mouse_h */
