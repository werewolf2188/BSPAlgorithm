//
//  RenderGraphics.hpp
//  BSPAlgorithm
//
//  Created by Enrique on 4/28/21.
//

#ifndef RenderGraphics_hpp
#define RenderGraphics_hpp

#include <SDL2/SDL.h>
#include <stdio.h>

#include "Structs.h"
#include "Graphics.h"
class RenderGraphics: public Graphics {
private:
    SDL_Texture* buffer;
    SDL_Renderer* renderer;
    SDL_Window * window;
    void* pixels;
    Rect frame;
public:
    RenderGraphics(SDL_Renderer* renderer, SDL_Window * window);

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

#endif /* RenderGraphics_hpp */
