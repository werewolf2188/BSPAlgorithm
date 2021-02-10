//
//  Loader.hpp
//  BSPAlgorithm
//
//  Created by Enrique on 2/8/21.
//

#ifndef Loader_hpp
#define Loader_hpp

#include <iostream>
#include <vector>
#include "Vector.h"
#include "Player.h"
#include "Sector.h"

class MapLoader {
private:
    std::vector<Vector2 *> vertices;
    std::vector<Sector *> sectors;
    Player *player;

    void loadVertex(std::fstream& file);
    void loadSector(std::fstream& file);
    void loadPlayer(std::fstream& file);
public:
    MapLoader(const char* fileName);
    ~MapLoader();
};

#endif /* Loader_hpp */
