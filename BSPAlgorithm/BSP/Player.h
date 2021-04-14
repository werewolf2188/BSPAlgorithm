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
    Player(Vector2 pos, float angle, unsigned int sector, float z);
    Vector3 getPosition();
    void setPosition(Vector3 position);
    Vector3 getVelocity();
    void setVelocity(Vector3 velocity);
    float getAngle();
    void setAngle(float angle);
    float getAnglesin();
    void setAnglesin(float anglesin); // For now, but if I can remove it later, I will
    float getAnglecos();
    void setAnglecos(float anglecos); // For now, but if I can remove it later, I will
    unsigned int getSector();
    void setSector(unsigned int sector);
    float getYaw();
    void setYaw(float yaw);
};

#endif /* Player_hpp */
