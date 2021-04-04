//
//  Sector.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 2/9/21.
//

#include "Sector.h"

Sector::Sector(float ceil, float floor): ceil(ceil), floor(floor) { }

std::vector<Vector2 *>& Sector::getVertices() {
    return vertices;
}

std::vector<signed char>& Sector::getNeighbors() {
    return neighbors;
}

unsigned int Sector::getNPoints() {
    return npoints;
}

void Sector::setNPoints(unsigned int npoints) {
    this->npoints = npoints;
}

float Sector::getCeil() {
    return ceil;
}

float Sector::getFloor() {
    return floor;
}
