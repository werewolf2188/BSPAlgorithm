//
//  RenderGraphics.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 4/28/21.
//

#include "RenderGraphics.h"

RenderGraphics::RenderGraphics(SDL_Renderer* renderer, SDL_Window * window):
renderer(renderer), window(window) { }

void RenderGraphics::drawPoint(Point p, Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawPoint(renderer, p.x, p.y);
}

void RenderGraphics::drawLine(Point from, Point to, Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawLine(renderer, from.x, from.y, to.x, to.y);
}

void RenderGraphics::drawRect(Rect r, Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_Rect rect = { r.position.x, r.position.y, r.size.width, r.size.height };
    SDL_RenderDrawRect(renderer, &rect);
}

void RenderGraphics::drawCircle(Point center, int radius, Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, center.x + x, center.y - y);
        SDL_RenderDrawPoint(renderer, center.x + x, center.y + y);
        SDL_RenderDrawPoint(renderer, center.x - x, center.y - y);
        SDL_RenderDrawPoint(renderer, center.x - x, center.y + y);
        SDL_RenderDrawPoint(renderer, center.x + y, center.y - x);
        SDL_RenderDrawPoint(renderer, center.x + y, center.y + x);
        SDL_RenderDrawPoint(renderer, center.x - y, center.y - x);
        SDL_RenderDrawPoint(renderer, center.x - y, center.y + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void RenderGraphics::drawDisk(Point center, int radius, Color color) {
    Size s = getDrawableSize();
    if(center.x + radius < 0 || center.x - radius >= s.width || center.y + radius < 0 || center.y - radius >= s.height) return; //every single pixel outside screen, so don't waste time on it
    int xc = center.x;
    int yc = center.y;
    int x = 0;
    int y = radius;
    int p = 3 - (radius << 1);
    int a, b, c, d, e, f, g, h;
    int pb = yc + radius + 1, pd = yc + radius + 1; //previous values: to avoid drawing horizontal lines multiple times  (ensure initial value is outside the range)
    while (x <= y)
    {
         // write data
        a = xc + x;
        b = yc + y;
        c = xc - x;
        d = yc - y;
        e = xc + y;
        f = yc + x;
        g = xc - y;
        h = yc - x;
        if(b != pb) drawLine({ a, b }, { c, b }, color);
        if(d != pd) drawLine({ a, d }, { c, d }, color);
        if(f != b)  drawLine({ e, f }, { e, f }, color);
        if(h != d && h != f) drawLine({ e, h }, { e, h }, color);
        pb = b;
        pd = d;
        if(p < 0) p += (x++ << 2) + 6;
        else p += ((x++ - y--) << 2) + 10;
    }
}

void RenderGraphics::clear() {
    // Memory leak using buffered texture
//    Size s = getDrawableSize();
//    buffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, s.width, s.height);
//    SDL_SetRenderTarget(renderer, buffer);
    SDL_SetRenderDrawColor(renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);
    SDL_RenderClear(renderer);
}

void RenderGraphics::update() {
    SDL_SetRenderTarget(renderer, NULL);
    // Memory leak using buffered texture
//    SDL_RenderCopy(renderer, buffer, NULL, NULL);
    SDL_RenderPresent(renderer);
}

Size RenderGraphics::getDrawableSize() const {
    Size s;
    SDL_GetWindowSize(this->window, &s.width, &s.height);
    return s;
};
