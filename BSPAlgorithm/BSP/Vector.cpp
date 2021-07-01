//
//  Vector.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 2/8/21.
//

#include "Vector.h"
#include "Math.h"

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

Vector2 operator+(Vector2 v1, Vector2 v2) {
    return { v1.x + v2.x, v1.y + v2.y};
}

Vector2 operator-(Vector2 v1, Vector2 v2) {
    return { v1.x - v2.x, v1.y - v2.y };
}

Vector3 operator+(Vector3 v1, Vector3 v2) {
    return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

Vector3 operator-(Vector3 v1, Vector3 v2) {
    return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

Vector3 operator+(Vector3 v1, Vector2 v2) {
    return { v1.x + v2.x, v1.y + v2.y, v1.z };
}

Vector3 operator-(Vector3 v1, Vector2 v2) {
    return { v1.x - v2.x, v1.y - v2.y, v1.z };
}

Vector3 operator+(Vector2 v1, Vector3 v2) {
    return { v1.x + v2.x, v1.y + v2.y, v2.z };
}

Vector3 operator-(Vector2 v1, Vector3 v2) {
    return { v1.x - v2.x, v1.y - v2.y, v2.z };
}

float crossProduct(Vector2 v0, Vector2 v1) {
    return vxs(v0.x, v0.y, v1.x, v1.y);
}

bool intersectBox(Vector2 v0, Vector2 v1, Vector2 v2, Vector2 v3) {
    return overlap(v0.x, v1.x, v2.x, v3.x) && overlap(v0.y, v1.y, v2.y, v3.y);
}

float pointSide(Vector2 p, Vector2 v0, Vector2 v1) {
    return vxs((v1.x)-(v0.x), (v1.y)-(v0.y), (p.x)-(v0.x), (p.y)-(v0.y));
}

Vector2 intersect(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4) {
    float dec = vxs((v1.x - v2.x), (v1.y - v2.y), (v3.x - v4.x), (v3.y - v4.y));
    float x = vxs(crossProduct(v1, v2), (v1.x - v2.x), crossProduct(v3, v4), (v3.x - v4.x)) / dec;
    float y = vxs(crossProduct(v1, v2), (v1.y - v2.y), crossProduct(v3, v4), (v3.y - v4.y)) / dec;
    Vector2 v = { x, y };
    return v;
}
