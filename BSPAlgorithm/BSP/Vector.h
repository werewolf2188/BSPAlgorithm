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

struct Vector3 {
    float x;
    float y;
    float z;
};

Vector3 * createVector3(float x, float y, float z);

#endif /* Vector_hpp */
