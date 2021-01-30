//
//  Color.h
//  BSPAlgorithm
//
//  Created by Enrique on 1/23/21.
//

#ifndef Color_h
#define Color_h
#include <stdint.h>
#include <iostream>
#include <SDL2/SDL_scancode.h>

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
extern Color RED;
extern Color GREEN;
extern Color BLUE;
extern Color CYAN;
extern Color MAGENTA;
extern Color YELLOW;
extern Color GRAY;
extern Color GREY;
extern Color MAROON;
extern Color DARKGREEN;
extern Color NAVY;
extern Color TEAL;
extern Color PURPLE;
extern Color OLIVE;

// MARK: Position

struct Point {
    int x;
    int y;
};

inline bool operator==(Point p1, Point p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

inline bool operator<(Point p1, Point p2) {
    return p1.x < p2.x && p1.y < p2.y;
}

inline bool operator<=(Point p1, Point p2) {
    return p1.x <= p2.x && p1.y <= p2.y;
}

inline bool operator>(Point p1, Point p2) {
    return p1.x > p2.x && p1.y > p2.y;
}

inline bool operator>=(Point p1, Point p2) {
    return p1.x >= p2.x && p1.y >= p2.y;
}

inline std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "( x: " << point.x << ", y: " << point.y << " )" << std::endl;
    return os;
}

inline Point min(Point p1, Point p2) {
    return p1 <= p2 ? p1 : p2;
}

inline Point max(Point p1, Point p2) {
    return p1 >= p2 ? p1 : p2;
}
// MARK: Size

struct Size {
    int width;
    int height;
};

inline bool operator==(Size s1, Size s2) {
    return s1.width == s2.width && s1.height == s2.height;
}

inline bool operator<(Size s1, Size s2) {
    return s1.width < s2.width && s1.height < s2.height;
}

inline bool operator<=(Size s1, Size s2) {
    return s1.width <= s2.width && s1.height <= s2.height;
}

inline bool operator>(Size s1, Size s2) {
    return s1.width > s2.width && s1.height > s2.height;
}

inline bool operator>=(Size s1, Size s2) {
    return s1.width >= s2.width && s1.height >= s2.height;
}

inline std::ostream& operator<<(std::ostream& os, const Size& size) {
    os << "( width: " << size.width << ", height: " << size.height << " )" << std::endl;
    return os;
}

inline Size min(Size s1, Size s2) {
    return s1 <= s2 ? s1 : s2;
}

inline Size max(Size s1, Size s2) {
    return s1 >= s2 ? s1 : s2;
}

// MARK: Rect

struct Rect {
    Point position;
    Size size;
};

inline bool operator==(Rect r1, Rect r2) {
    return r1.position == r2.position && r1.size == r2.size;
}

inline bool operator<(Rect r1, Rect r2) {
    return r1.position < r2.position && r1.size < r2.size;
}

inline bool operator<=(Rect r1, Rect r2) {
    return r1.position <= r2.position && r1.size <= r2.size;
}

inline bool operator>(Rect r1, Rect r2) {
    return r1.position > r2.position && r1.size > r2.size;
}

inline bool operator>=(Rect r1, Rect r2) {
    return r1.position >= r2.position && r1.size >= r2.size;
}

inline std::ostream& operator<<(std::ostream& os, const Rect& rect) {
    os << "( position: " << rect.position << ", size: " << rect.size << " )" << std::endl;
    return os;
}

inline Rect min(Rect r1, Rect r2) {
    return r1 <= r2 ? r1 : r2;
}

inline Rect max(Rect r1, Rect r2) {
    return r1 >= r2 ? r1 : r2;
}
#endif /* Color_h */
