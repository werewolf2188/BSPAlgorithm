//
//  Color.h
//  BSPAlgorithm
//
//  Created by Enrique on 1/23/21.
//

#ifndef Color_h
#define Color_h
#include <stdint.h>

// MARK: Color
struct Color {
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t a;
};

Color makeFromRGBA(long color);
Color makeFromRGB(long color);

extern Color WHITE;
extern Color BLACK;

// MARK: Position

struct Point {
    int x;
    int y;
};

// MARK: Size

struct Size {
    int width;
    int height;
};

// MARK: Rect

struct Rect {
    Point position;
    Size size;
};
#endif /* Color_h */
