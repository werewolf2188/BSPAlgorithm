//
//  main.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 1/23/21.
//

#include <iostream>
#include "Classes/Window.h"

#define TEST 0

#if TEST
#include "Classes/UserInputGameLoop.h"
#include "Test/Boundaries.h"
#include "Test/Player.h"
#include "Test/AbsoluteMap.h"
#include "Test/TransformedMap.h"
#include "Test/PerspectiveTransformedMap.h"
#else
#include "Classes/PollingGameLoop.h"
#include "BSP/Constants.h"
#include "BSP/Loader.h"
#include "BSP/Math.h"
#include "BSP/MapSprite.h"
#endif

int main(int argc, const char * argv[]) {
    
#if TEST
    GameLoop *gameLoop = new UserInputGameLoop;
    Player player = { 130, 130, M_PI };
    Wall wall = { { 70, 100 }, { 70, 150} };
    AbsoluteMapSprite amSprite(player, wall);
    TransformedMapSprite tmSprite(player, wall);
    PerspectiveTransformedMapSprite ptmSprite(player, wall);
    
    gameLoop->addSprites(&amSprite);
    gameLoop->addSprites(&tmSprite);
    gameLoop->addSprites(&ptmSprite);
#else
    GameLoop *gameLoop = new PollingGameLoop;
    MapLoader loader("map-clear.txt");
    MapSprite map(loader);
    gameLoop->addSprites(&map);
#endif
    Window w(gameLoop);
    w.show();
    return 0;
}
