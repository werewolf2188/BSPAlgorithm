//
//  Vector.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 2/8/21.
//

#include "Vector.h"

Vector2 * createVector2(float x, float y) {
    Vector2 * vertex = new Vector2;
    vertex->x = x;
    vertex->y = y;
    return vertex;
}

Vector3 * createVector3(float x, float y, float z) {
    Vector3 * vertex = new Vector3;
    vertex->x = x;
    vertex->y = y;
    vertex->z = z;
    return vertex;
}
