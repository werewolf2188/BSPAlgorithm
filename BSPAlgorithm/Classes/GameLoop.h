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
class GameLoop {
private:
    Graphics* graphics;
public:
    GameLoop();
    ~GameLoop();
    void start(Graphics* graphics);
};
#endif /* GameLoop_hpp */
