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
    SDL_ShowCursor(SDL_DISABLE);
    this->graphics = graphics;
    bool quit = false;
    bool needRender = true;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            for(auto sprite: this->sprites) {
                
                // Need two improve this loop
                // Key down
                
                if (e.type == SDL_KEYDOWN) {
                    const Key key = SDL_GetKeyboardState(NULL);
                    KeyListener* keyListener =
                        dynamic_cast<KeyListener *>(sprite);
                    if (keyListener) {
                        needRender = keyListener->onKeyPress(key);
                    }
                }
                if (e.type == SDL_KEYUP) {
                    const Key key = e.key.keysym.scancode;
                    KeyListener* keyListener =
                        dynamic_cast<KeyListener *>(sprite);
                    if (keyListener) {
                        needRender = keyListener->onKeyRelease(key);
                    }
                }
                
                // Mouse motion
                
                if (e.type == SDL_MOUSEMOTION) {
                    MouseListener* mouseListener =
                        dynamic_cast<MouseListener *>(sprite);
                    Point p;
                    if (mouseListener) {
                        SDL_GetMouseState(&p.x, &p.y);
                        needRender |= mouseListener->onMouseMove(p);
                        SDL_GetRelativeMouseState(&p.x, &p.y);
                        needRender |= mouseListener->onRelativeMouse(p);
                    }
                }
                
                // Render
                
                
            }
            if (needRender) {
                this->graphics->clear();
                for(auto sprite: this->sprites) {
                    // Need to improve the rendering system
                    sprite->onRender(graphics);
                }
                this->graphics->update();
                needRender = false;
            }
        }
    }
}
