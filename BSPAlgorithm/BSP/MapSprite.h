//
//  MapSprite.hpp
//  BSPAlgorithm
//
//  Created by Enrique on 3/25/21.
//

#ifndef MapSprite_hpp
#define MapSprite_hpp

#include "Loader.h"
#include "../Classes/Sprite.h"
#include "../Classes/Keyboard.h"
#include "../Classes/Mouse.h"
class MapSprite: public Sprite, public KeyListener, public MouseListener {
private:
    MapLoader& loader;
    Player player;

    // This could belong to the player at some point
    bool ground = false;
    bool falling = true;
    bool moving = false;
    bool ducking = false;

    float yawVar = 0;

    float yaw(float y, float z);
    void draw_vertical_line(Graphics* g,
                            int x,
                            int y1,
                            int y2,
                            Color top,
                            Color middle,
                            Color bottom,
                            Size windowSize);

    void handle_falling();
    void handle_moving();
    float current_eye_height();
    void move_player(float dx, float dy);
    
public:
    MapSprite(MapLoader& loader);
    bool onKeyPress(const Key& key);
    void onRender(Graphics *g);
    bool onRelativeMouse(Point p);
};
#endif /* MapSprite_hpp */
