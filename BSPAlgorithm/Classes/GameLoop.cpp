//
//  GameLoop.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 1/25/21.
//

#include "GameLoop.h"
#include <SDL2/SDL.h>

GameLoop::GameLoop() {
    
}

GameLoop::~GameLoop() {
    delete graphics;
}

void GameLoop::start(Graphics* graphics) {
    SDL_Event e;
    this->graphics = graphics;
    Rect r = {{ 100, 100}, {50, 50} };
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN) {
                this->graphics->clear();
                const Uint8 *state = SDL_GetKeyboardState(NULL);
                if (state[SDL_SCANCODE_RIGHT]) {
                    r.position.x += 5;
                }
                if (state[SDL_SCANCODE_LEFT]) {
                    
                    r.position.x -= 5;
                }
                if (state[SDL_SCANCODE_UP]) {
                    r.position.y -= 5;
                }
                if (state[SDL_SCANCODE_DOWN]) {
                    
                    r.position.y += 5;
                }
            }
            this->graphics->drawRect(r, BLACK);
            this->graphics->update();
        }
    }
}
