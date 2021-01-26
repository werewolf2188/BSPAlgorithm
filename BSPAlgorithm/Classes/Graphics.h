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
    uint32_t* pixels;
    Rect frame;    
public:
    Graphics(SDL_Surface* surface, SDL_Window * window);

    void drawPoint(Point p, Color c);
    void drawLine(Point from, Point to, Color c);
    void drawRect(Rect r, Color c);
    void drawCircle(Point center, int radius, Color color);
    void drawDisk(Point center, int radius, Color color);
    void clear();
    void update();
};

#endif /* Graphics_hpp */
