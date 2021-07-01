//
//  PollingGameLoop.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 4/30/21.
//

#include "PollingGameLoop.h"
#include <SDL2/SDL.h>
#include "Keyboard.h"
#include "Mouse.h"

struct KeyEvent {
    Key key = nullptr;
    Uint32 event;
};

PollingGameLoop::PollingGameLoop() {
    
}

PollingGameLoop::~PollingGameLoop() {
    delete graphics;
}

void PollingGameLoop::addSprites(Sprite *sprite) {
    this->sprites.push_back(sprite);
}

void PollingGameLoop::start(Graphics* graphics, UI* ui) {
    SDL_ShowCursor(SDL_DISABLE);
    this->graphics = graphics;
    bool quit = false;

    KeyEvent * keyEvent = nullptr;

    while (!quit) {
        ui->getUserInputHandler();
        // Render first
        this->graphics->clear();
        bool needUI = false;
        for(auto sprite: this->sprites) {
            sprite->onRender(graphics);
            if (ui) {
                needUI = sprite->onUI(ui);
            }
        }
        if (needUI) {
            ui->refresh();
        }
        this->graphics->update();
        SDL_Event e;
        
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN) {
                const Key key = SDL_GetKeyboardState(NULL);
                if (key == SDL_SCANCODE_Q) {
                    quit = true;
                    break;
                }
                KeyEvent k;
                k.key = key;
                k.event = e.type;
                keyEvent = &k;
            }
            if (e.type == SDL_KEYUP) {
                const Key key = e.key.keysym.scancode;
                KeyEvent k;
                k.key = key;
                k.event = e.type;
                keyEvent = &k;
            }
        }
        for(auto sprite: this->sprites) {
            // Key stroke while asking
            KeyListener* keyListener =
                dynamic_cast<KeyListener *>(sprite);
            if (keyListener) {
                if (keyEvent) {
                    switch (keyEvent->event) {
                        case SDL_KEYDOWN:
                            keyListener->onKeyPress(keyEvent->key);
                            break;
                        case SDL_KEYUP:
                            if (keyListener->onKeyRelease(keyEvent->key)) {
                                keyEvent = nullptr;
                            }                            
                            break;
                        default:
                            break;
                    }
                }
            }
            // Mouse motion without asking
            MouseListener* mouseListener =
                dynamic_cast<MouseListener *>(sprite);
            Point p;
            if (mouseListener) {
                SDL_GetMouseState(&p.x, &p.y);
                mouseListener->onMouseMove(p);
                SDL_GetRelativeMouseState(&p.x, &p.y);
                mouseListener->onRelativeMouse(p);
            }
        }
        SDL_Delay(10);
    }
}
