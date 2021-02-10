//
//  Player.hpp
//  BSPAlgorithm
//
//  Created by Enrique on 2/8/21.
//

#ifndef Player_hpp
#define Player_hpp

#include "Vector.h"

class Player {
private:
    Vector3 position;
    Vector3 velocity;
    float angle;
    float anglesin;
    float anglecos;
    float yaw;
    unsigned int sector;
public:
    Player(Vector2 pos, float angle, unsigned int sector);
};

#endif /* Player_hpp */
