//
//  Window.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 1/23/21.
//

#include "Window.h"
#include "Graphics.h"

// MARK: Private methods
void Window::initialize_window() {
    if(SDL_Init(SDL_INIT_VIDEO) >= 0 ) {
        SDL_DisplayMode mode = { SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0 };
        SDL_GetCurrentDisplayMode(0, &mode);
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mode.w, mode.h, SDL_WINDOW_SHOWN);
    }
};

void Window::initialize_surface() {
    if (window) {
        surface = SDL_GetWindowSurface(window);
        SDL_FillRect(surface, NULL, SDL_MapRGB( surface->format, WHITE.r, WHITE.g, WHITE.b));
        SDL_UpdateWindowSurface(window);
    }
};

void Window::initialize_event_loop() {
    if (window) {
        SDL_Event e;
        bool quit = false;
        while (!quit) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }
        }
    }
};

// MARK: Public methods
Window::Window() {
    initialize_window();
    initialize_surface();
};

Window::~Window() {
    SDL_DestroyWindow(window);
    //Quit SDL subsystems
    SDL_Quit();
}

void Window::show() {
    initialize_event_loop();
}

Rect Window::getFrame() {
    return { getPosition(), getSize() };
}

Size Window::getSize() {
    Size s;
    SDL_GetWindowSize(this->window, &s.width, &s.height);
    return s;
}

Point Window::getPosition() {
    Point p;
    SDL_GetWindowPosition(this->window, &p.x, &p.y);
    return p;
}

Graphics* Window::getGraphics() {
    return new Graphics(surface, window, getFrame());
}
