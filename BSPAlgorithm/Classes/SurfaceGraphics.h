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
#include "Graphics.h"
class SurfaceGraphics: public Graphics {
private:
    SDL_Surface* buffer;
    SDL_Surface* surface;
    SDL_Window * window;
    void* pixels;
    Rect frame;    
public:
    SurfaceGraphics(SDL_Surface* surface, SDL_Window * window);

    void drawPoint(Point p, Color c);
    void drawLine(Point from, Point to, Color c);
    void drawRect(Rect r, Color c);
    void drawCircle(Point center, int radius, Color color);
    void drawDisk(Point center, int radius, Color color);
    void clear();
    void update();
public:
    Size getDrawableSize() const;
};

#endif /* Graphics_hpp */
