//
//  Loader.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 2/8/21.
//

#include "Loader.h"
#include <fstream>
#include <string>
#include <cassert>

#include <stdio.h>

#include "Constants.h"

#define EQUALS(type, string) !type.compare(string)
// DELETE
// One # for string value
#define LOL(x) #x
//


MapLoader::MapLoader(const char * fileName) {
    std::fstream file(fileName, std::fstream::in);
    assert(file.is_open());
    
    std::string type;
    while(!file.eof()) {
        file >> type;
        if (EQUALS(type, "vertex")) {
            loadVertex(file);   
        } else if (EQUALS(type, "sector")) {
            loadSector(file);
        } else if (EQUALS(type, "player")) {
            loadPlayer(file);
        }
        type = "";
    }
    file.close();
}

void MapLoader::loadVertex(std::fstream& file) {
    // format is 'vertex    y   x x x etc.
    float y;
    file >> y;
    while(file.peek() != '\n') {
        float x;
        file >> x;
        Vector2 * vertex = createVector2(x, y);
        vertices.push_back(vertex);
    }
}

void MapLoader::loadSector(std::fstream& file) {
    float ceil, floor;
    file >> floor;
    file >> ceil;
    Sector * sector = new Sector(ceil, floor);

    std::vector<int> nums;
    int num;
    char *temp;
    while(file.peek() != '\n') {
        file >> num;
        temp = ((char *)&num);
        if (temp[0] == 'x') nums.push_back(-1);
        else nums.push_back(num);
    }
    sector->setNPoints((unsigned int) nums.size() / 2);
    
    for (int n = 0; n < nums.size() / 2; n++) {
        char neighbor = (signed char) nums[(nums.size() / 2) + n];
        sector->getNeighbors().push_back(neighbor);
    }
    
    for (int n = 0; n < nums.size() / 2; n++) {
        Vector2* vertex = vertices[nums[n]];
        sector->getVertices().push_back(vertex);
    }
    /*
     sect->vertex[0] = sect->vertex[m];
     */
    Vector2 *last = sector->getVertices()[sector->getVertices().size() - 1];
    sector->getVertices().insert(sector->getVertices().begin(), last);
    sectors.push_back(sector);
}

void MapLoader::loadPlayer(std::fstream& file) {
    // format is 'player    x y angle sector.
    Vector2 position;
    float angle;
    int sector;
    file >> position.x;
    file >> position.y;
    file >> angle;
    file >> sector;
    float z = sectors[sector]->getFloor() + EyeHeight;
    player = new Player(position, angle, sector, z);
}

MapLoader::~MapLoader() {
    vertices.clear();
    sectors.clear();
    delete player;
}

std::vector<Vector2 *> MapLoader::getVertices() {
    return vertices;
}

std::vector<Sector *> MapLoader::getSectors() {
    return sectors;
}

Player MapLoader::getPlayerInitialLocation() {
    return *player;
}
