//
//  Sector.hpp
//  BSPAlgorithm
//
//  Created by Enrique on 2/9/21.
//

#ifndef Sector_hpp
#define Sector_hpp

#include <vector>
#include "Vector.h"

class Sector {
private:
    float ceil;
    float floor;
    std::vector<Vector2 *> vertices;
    std::vector<signed char> neighbors;
    unsigned int npoints;
public:
    Sector(float ceil, float floor);
    std::vector<Vector2 *>& getVertices();
    std::vector<signed char>& getNeighbors();
    unsigned int getNPoints();
    void setNPoints(unsigned int npoints);
};

#endif /* Sector_hpp */
