//
//  Color.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 1/23/21.
//

#include <stdio.h>
#include "Structs.h"

Color makeFromRGBA(long color) {
    uint8_t r = (color & 0xFF000000) >> 24;
    uint8_t g = (color & 0x00FF0000) >> 16;
    uint8_t b = (color & 0x0000FF00) >> 8;
    uint8_t a = color & 0x000000FF;
    return { b, g, r, a };
}

Color makeFromRGB(long color) {
    if (color < 0xFFFF) {
        return { 0, 0, 0, 0};
    }
    uint8_t r = (color & 0xFF0000) >> 16;
    uint8_t g = (color & 0x00FF00) >> 8;
    uint8_t b = (color & 0x0000FF);
    return { b, g, r, 0xFF };
}

Color WHITE = makeFromRGBA(0xFFFFFFFF);
Color BLACK = makeFromRGBA(0x00000000);
Color RED = makeFromRGBA(0xFF0000FF);
Color GREEN = makeFromRGBA(0x00FF00FF);
Color BLUE = makeFromRGBA(0x0000FFFF);
