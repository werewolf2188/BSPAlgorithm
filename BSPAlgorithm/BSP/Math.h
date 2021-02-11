//
//  Math.h
//  BSPAlgorithm
//
//  Created by Enrique on 2/10/21.
//

#ifndef Math_h
#define Math_h

#include <iostream>

template <class T>
inline T clamp(T value, T min, T max) {
    return std::min(std::max(value,min),max);
}

template <class T>
inline T vxs(T x0, T y0, T x1, T y1) {
    return ((x0)*(y1) - (x1)*(y0));
}

template <class T>
inline bool overlap(T a0, T a1, T b0, T b1) {
    return (std::min(a0,a1) <= std::max(b0,b1) && std::min(b0,b1) <= std::max(a0,a1));
}

#endif /* Math_h */
