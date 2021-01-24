//
//  Graphics.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 1/23/21.
//

#include "Graphics.h"

void Graphics::drawTest() {
    for (int x = 30000; x < 35000; x++) {
        *(((uint32_t*) surface->pixels) + x) = 0x00000000;
    }
    SDL_UpdateWindowSurface(window);
}

void Graphics::drawPoint(Point p, Color c) {
    // Dont pass the actual frame
    uint32_t pixel = (p.x + (p.y * frame.size.width));
    *(((uint32_t*) surface->pixels) + pixel) = 0x00000000;
    SDL_UpdateWindowSurface(window);
}
