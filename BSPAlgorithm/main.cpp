//
//  main.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 1/23/21.
//

#include <iostream>
#include "Classes/Window.h"
#include "Classes/GameLoop.h"

#define TEST 1

#ifdef TEST
#include "Test/Boundaries.h"
#include "Test/Player.h"
#include "Test/AbsoluteMap.h"
#include "Test/TransformedMap.h"
#include "Test/PerspectiveTransformedMap.h"
#endif

int main(int argc, const char * argv[]) {
    // insert code here...
#ifdef TEST
    Player player = { 130, 130, M_PI };
    Wall wall = { { 70, 100 }, { 70, 150} };
    AbsoluteMapSprite amSprite(player, wall);
    TransformedMapSprite tmSprite(player, wall);
    PerspectiveTransformedMapSprite ptmSprite(player, wall);
    GameLoop gameLoop;
    gameLoop.addSprites(&amSprite);
    gameLoop.addSprites(&tmSprite);
    gameLoop.addSprites(&ptmSprite);
    Window w(&gameLoop);
#else
    GameLoop gameLoop;
    Window w(&gameLoop);
#endif
    
    w.show();
    return 0;
}
