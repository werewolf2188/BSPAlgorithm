//
//  Window.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 1/23/21.
//

#include "Window.h"
#define NEW_DRAWING_ENGINE 1

#if NEW_DRAWING_ENGINE
#include "RenderGraphics.h"
#else
#include "SurfaceGraphics.h"
#endif

// MARK: Private methods
void Window::initialize_window() {
#if NEW_DRAWING_ENGINE
    ui = new UI();
#endif
    if(SDL_Init(SDL_INIT_VIDEO) >= 0 ) {
        SDL_DisplayMode mode = { SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0 };
        SDL_GetCurrentDisplayMode(0, &mode);
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mode.w, mode.h, SDL_WINDOW_SHOWN);
    }
};

void Window::initialize_graphics() {
    if (window) {
#if NEW_DRAWING_ENGINE
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        SDL_SetRenderDrawColor(renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        SDL_DisplayMode mode = { SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0 };
        SDL_GetCurrentDisplayMode(0, &mode);
        ui->initialize(window, renderer, { mode.w, mode.h });
#else
        surface = SDL_GetWindowSurface(window);
        SDL_FillRect(surface, NULL, SDL_MapRGB( surface->format, WHITE.r, WHITE.g, WHITE.b));
        SDL_UpdateWindowSurface(window);
#endif
        
    }
};

void Window::initialize_event_loop() {
    if (window) {
        if (gameLoop) {
            gameLoop->start(getGraphics(), ui);
        }
    }
};

// MARK: Public methods
Window::Window(GameLoop* gameLoop): gameLoop(gameLoop) {
    initialize_window();
    initialize_graphics();
};

Window::~Window() {
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
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
#if NEW_DRAWING_ENGINE
    return new RenderGraphics(renderer, window);
#else
    return new SurfaceGraphics(surface, window);
#endif
}
