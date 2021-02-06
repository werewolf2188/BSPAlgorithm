//
//  Player.hpp
//  BSPAlgorithm
//
//  Created by Enrique on 1/30/21.
//

#ifndef Player_hpp
#define Player_hpp

#include <iostream>
#include "../Classes/Structs.h"
#include "../Classes/Keyboard.h"
struct Player {
    Point position;
    double angle;
};

bool handleKeyboard(Player &player, const Key& key);

std::ostream& operator<<(std::ostream& os, const Player& player);
#endif /* Player_hpp */
