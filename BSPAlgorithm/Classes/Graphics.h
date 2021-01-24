//
//  Graphics.hpp
//  BSPAlgorithm
//
//  Created by Enrique on 1/23/21.
//

#ifndef Graphics_hpp
#define Graphics_hpp
#include <SDL2/SDL.h>
#include <stdio.h>

#include "Structs.h"
class Graphics {
private:
    SDL_Surface* surface;
    SDL_Window * window;
    Rect frame;
public:
    Graphics(SDL_Surface* surface, SDL_Window * window, Rect frame):
    surface(surface), window(window), frame(frame) {}
    void drawTest();

    void drawPoint(Point p, Color c);
};

#endif /* Graphics_hpp */
