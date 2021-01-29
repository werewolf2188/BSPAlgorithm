//
//  GameLoop.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 1/25/21.
//

#include "GameLoop.h"
#include <SDL2/SDL.h>
#include "Keyboard.h"
#include "Mouse.h"

GameLoop::GameLoop() {
    
}

GameLoop::~GameLoop() {
    delete graphics;
}

void GameLoop::addSprites(Sprite *sprite) {
    this->sprites.push_back(sprite);
}

void GameLoop::start(Graphics* graphics) {
    SDL_Event e;
    this->graphics = graphics;
    bool quit = false;
    bool needRender = true;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            for(auto sprite: this->sprites) {
                
                // Key down
                
                if (e.type == SDL_KEYDOWN) {
                    needRender = true;
                    const Key key = SDL_GetKeyboardState(NULL);
                    KeyListener* keyListener =
                        dynamic_cast<KeyListener *>(sprite);
                    if (keyListener) {
                        keyListener->onKeyPress(key);
                    }
                }
                
                // Mouse motion
                
                if (e.type == SDL_MOUSEMOTION) {
                    needRender = true;
                    MouseListener* mouseListener =
                        dynamic_cast<MouseListener *>(sprite);
                    Point p;
                    if (mouseListener) {
                        SDL_GetMouseState(&p.x, &p.y);
                        mouseListener->onMouseMove(p);
                    }
                    
                }
                
                // Render
                
                if (needRender) {
                    this->graphics->clear();
                    sprite->onRender(graphics);
                    this->graphics->update();
                    needRender = false;
                }
            }
            
        }
    }
}
