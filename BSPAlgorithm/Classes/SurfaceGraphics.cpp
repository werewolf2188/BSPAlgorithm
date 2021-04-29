//
//  Graphics.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 1/23/21.
//

#include "SurfaceGraphics.h"
#include <cmath>

// MARK: Helpers
union ColorUnion {
    uint32_t argb;
    Color color;
};

int _fromColor(Color c) {
    ColorUnion un;
    un.color = c;
    return un.argb;
}

void _drawPoint(SDL_Surface* surface, Point p, Color c) {
    if (p.x < 0 || p.y < 0 || p.x > surface->w || p.y > surface->h) return;
    uint32_t pixel = (p.x + (p.y * surface->w));
    *(((uint32_t*)surface->pixels) + pixel) = _fromColor(c);
}

void _horLine(SDL_Surface* surface, int y, int x1, int x2, Color c) {
    if(x2 < x1) {x1 += x2; x2 = x1 - x2; x1 -= x2;} //swap x1 and x2, x1 must be the leftmost endpoint
    if(x2 < 0 || x1 >= surface->w || y < 0 || y >= surface->h) return; //no single point of the line is on screen
    if(x1 < 0) x1 = 0; //clip
    if(x2 >= surface->w) x2 = surface->w - 1; //clip
    
    for(int x = x1; x <= x2; x++) {
        _drawPoint(surface, { x, y }, c);
    }
}

void _verLine(SDL_Surface* surface, int x, int y1, int y2, Color c) {
    if(y2 < y1) {y1 += y2; y2 = y1 - y2; y1 -= y2;} //swap y1 and y2
    if(y2 < 0 || y1 >= surface->h  || x < 0 || x >= surface->w) return ; //no single point of the line is on screen
    if(y1 < 0) y1 = 0; //clip
    if(y2 >= surface->w) y2 = surface->h - 1; //clip
    
    for(int y = y1; y <= y2; y++) {
        _drawPoint(surface, { x, y }, c);
    }
}

void _drawLine(SDL_Surface* surface, int x1, int y1, int x2, int y2, Color c) {
    if(x1 < 0 || x1 > surface->w - 1 || x2 < 0 || x2 > surface->w - 1 || y1 < 0 || y1 > surface->h - 1 || y2 < 0 || y2 > surface->h - 1) return;

    int deltax = std::abs(x2 - x1); //The difference between the x's
    int deltay = std::abs(y2 - y1); //The difference between the y's
    int x = x1; //Start x off at the first pixel
    int y = y1; //Start y off at the first pixel
    int xinc1, xinc2, yinc1, yinc2, den, num, numadd, numpixels, curpixel;

    if(x2 >= x1) //The x-values are increasing
    {
        xinc1 = 1;
        xinc2 = 1;
    }
    else //The x-values are decreasing
    {
        xinc1 = -1;
        xinc2 = -1;
    }
    if(y2 >= y1) //The y-values are increasing
    {
        yinc1 = 1;
        yinc2 = 1;
    }
    else //The y-values are decreasing
    {
        yinc1 = -1;
        yinc2 = -1;
    }
    if (deltax >= deltay) //There is at least one x-value for every y-value
    {
        xinc1 = 0; //Don't change the x when numerator >= denominator
        yinc2 = 0; //Don't change the y for every iteration
        den = deltax;
        num = deltax / 2;
        numadd = deltay;
        numpixels = deltax; //There are more x-values than y-values
    }
    else //There is at least one y-value for every x-value
    {
        xinc2 = 0; //Don't change the x for every iteration
        yinc1 = 0; //Don't change the y when numerator >= denominator
        den = deltay;
        num = deltay / 2;
        numadd = deltax;
        numpixels = deltay; //There are more y-values than x-values
    }

    for (curpixel = 0; curpixel <= numpixels; curpixel++)
    {
        _drawPoint(surface, { x % surface->w, y % surface->h }, c);  //Draw the current pixel
        num += numadd;  //Increase the numerator by the top of the fraction
        if (num >= den) //Check if numerator >= denominator
        {
            num -= den; //Calculate the new numerator value
            x += xinc1; //Change the x as appropriate
            y += yinc1; //Change the y as appropriate
        }
        x += xinc2; //Change the x as appropriate
        y += yinc2; //Change the y as appropriate
    }
}

// MARK: Graphics
SurfaceGraphics::SurfaceGraphics(SDL_Surface* surface, SDL_Window * window):
surface(surface), window(window) {}

void SurfaceGraphics::drawPoint(Point p, Color c) {
    // Dont pass the actual frame
    _drawPoint(buffer, p, c);
}

void SurfaceGraphics::drawLine(Point from, Point to, Color c) {
    if (from == to) drawPoint(from, c);
    else if (from.y == to.y) _horLine(buffer, to.y, from.x, to.x, c);
    else if (from.x == to.x) _verLine(buffer, to.x, from.y, to.y, c);
    else _drawLine(buffer, from.x, from.y, to.x, to.y, c);
}

void SurfaceGraphics::drawRect(Rect r, Color c) {
    int x0 = r.position.x;
    int y0 = r.position.y;
    int x1 = r.position.x + r.size.width;
    int y1 = r.position.y + r.size.height;
    drawLine({ x0, y0}, {x1, y0}, c);
    drawLine({ x0, y0}, {x0, y1}, c);
    drawLine({ x0, y1}, {x1, y1}, c);
    drawLine({ x1, y0}, {x1, y1}, c);
}

void SurfaceGraphics::drawCircle(Point center, int radius, Color color) {
    int xc = center.x;
    int yc = center.y;
    if(xc - radius < 0 || xc + radius >= surface->w || yc - radius < 0 || yc + radius >= surface->h) return;
    int x = 0;
    int y = radius;
    int p = 3 - (radius << 1);
    int a, b, c, d, e, f, g, h;
    while (x <= y)
    {
        a = xc + x; //8 pixels can be calculated at once thanks to the symmetry
        b = yc + y;
        c = xc - x;
        d = yc - y;
        e = xc + y;
        f = yc + x;
        g = xc - y;
        h = yc - x;
        drawPoint({a, b}, color);
        drawPoint({c, d}, color);
        drawPoint({e, f}, color);
        drawPoint({g, f}, color);
        if(x > 0) //avoid drawing pixels at same position as the other ones
        {
            drawPoint({a, d}, color);
            drawPoint({c, b}, color);
            drawPoint({e, h}, color);
            drawPoint({g, h}, color);
        }
        if(p < 0) p += (x++ << 2) + 6;
        else p += ((x++ - y--) << 2) + 10;
    }
}

void SurfaceGraphics::drawDisk(Point center, int radius, Color color) {
    if(center.x + radius < 0 || center.x - radius >= surface->w || center.y + radius < 0 || center.y - radius >= surface->h) return; //every single pixel outside screen, so don't waste time on it
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
        if(b != pb) _horLine(buffer, b, a, c, color);
        if(d != pd) _horLine(buffer, d, a, c, color);
        if(f != b)  _horLine(buffer, f, e, g, color);
        if(h != d && h != f) _horLine(buffer, h, e, g, color);
        pb = b;
        pd = d;
        if(p < 0) p += (x++ << 2) + 6;
        else p += ((x++ - y--) << 2) + 10;
    }
}

void SurfaceGraphics::update() {
    SDL_memcpy(surface->pixels, buffer->pixels, surface->w * surface->h * sizeof(uint32_t));
    SDL_UpdateWindowSurface(window);
    SDL_FreeSurface(buffer);
}

void SurfaceGraphics::clear() {
    buffer = SDL_DuplicateSurface(surface);
    SDL_FillRect(buffer, NULL, SDL_MapRGB( surface->format, WHITE.r, WHITE.g, WHITE.b));
}

Size SurfaceGraphics::getDrawableSize() const {
    Size s;
    SDL_GetWindowSize(this->window, &s.width, &s.height);
    return s;
}
