//
//  main.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 1/23/21.
//

#include <iostream>
#include "Classes/Window.h"
#include "Classes/GameLoop.h"
#include "Classes/Keyboard.h"
#include "Classes/Mouse.h"

// Example of class with sprite, key listener and mouse listener
class RectangleSprite: public Sprite, public KeyListener, public MouseListener {
private:
    Rect r;
public:
    RectangleSprite();
    void onKeyPress(const Key& key);
    void onMouseMove(Point p);
    void onRender(Graphics *g);
};

RectangleSprite::RectangleSprite() {
    this->r = { { 100, 100 }, {50, 50} };
}

void RectangleSprite::onKeyPress(const Key& key) {
    if (key == SDL_SCANCODE_RIGHT) {
        r.position.x += 5;
    }
    if (key == SDL_SCANCODE_LEFT) {
        
        r.position.x -= 5;
    }
    if (key == SDL_SCANCODE_UP) {
        r.position.y -= 5;
    }
    if (key == SDL_SCANCODE_DOWN) {
        r.position.y += 5;
    }
}

void RectangleSprite::onMouseMove(Point p) {
    r.position.x = p.x;
    r.position.y = p.y;
}

void RectangleSprite::onRender(Graphics *g) {
    g->drawRect(r, BLACK);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    RectangleSprite rect;
    GameLoop gameLoop;
    gameLoop.addSprites(&rect);
    Window w(&gameLoop);
    w.show();
    return 0;
}

//    Graphics g = w.getGraphics();
//    g.drawLine({ 100, 100 }, { 300, 200} , RED); //DIAGONAL
//    g.drawLine({ 100, 100 }, { 100, 300} , GREEN); //VERTICAL
//    g.drawLine({ 100, 100 }, { 300, 100} , BLUE); //HORIZONTAL
//    g.drawRect({{ 1200, 800}, {50, 50}}, BLACK);
//    g.drawCircle({ 500, 500 }, 50, BLACK);
//    g.drawDisk({ 700, 500 }, 50, BLACK);
//    g.update();
//    g.clear();
