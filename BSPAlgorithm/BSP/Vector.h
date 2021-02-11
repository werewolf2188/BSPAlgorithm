//
//  Vector.hpp
//  BSPAlgorithm
//
//  Created by Enrique on 2/8/21.
//

#ifndef Vector_hpp
#define Vector_hpp

struct Vector2 {
    float x;
    float y;
};

Vector2 * createVector2(float x, float y);
float crossProduct(Vector2 v0, Vector2 v1);
bool intersectBox(Vector2 v0, Vector2 v1, Vector2 v2, Vector2 v3);
float pointSide(Vector2 p, Vector2 v0, Vector2 v1);
Vector2 intersect(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4);

struct Vector3 {
    float x;
    float y;
    float z;
};

Vector3 * createVector3(float x, float y, float z);

#endif /* Vector_hpp */
