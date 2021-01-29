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
class BoundariesSprite: public Sprite/*, public KeyListener, public MouseListener*/ {
private:
    Rect r;
    Color color;
public:
    BoundariesSprite(Rect r, Color color);
//    bool onKeyPress(const Key& key);
//    bool onMouseMove(Point p);
    void onRender(Graphics *g);
};

int main(int argc, const char * argv[]) {
    // insert code here...
    BoundariesSprite boundaries({ { 100, 100 }, {200, 300} }, BLUE);
    BoundariesSprite boundaries2({ { 350, 100 }, {200, 300} }, RED);
    BoundariesSprite boundaries3({ { 600, 100 }, {200, 300} }, DARKGREEN);
    GameLoop gameLoop;
    gameLoop.addSprites(&boundaries);
    gameLoop.addSprites(&boundaries2);
    gameLoop.addSprites(&boundaries3);
    Window w(&gameLoop);
    w.show();
    return 0;
}

//<=========================

BoundariesSprite::BoundariesSprite(Rect r, Color color): r(r), color(color) { }

//bool BoundariesSprite::onKeyPress(const Key& key) {
//    bool keyStrokeHandled = false;
//    if (key == SDL_SCANCODE_RIGHT) {
//        r.position.x += 5;
//        keyStrokeHandled = true;
//    }
//    if (key == SDL_SCANCODE_LEFT) {
//        r.position.x -= 5;
//        keyStrokeHandled = true;
//    }
//    if (key == SDL_SCANCODE_UP) {
//        r.position.y -= 5;
//        keyStrokeHandled = true;
//    }
//    if (key == SDL_SCANCODE_DOWN) {
//        r.position.y += 5;
//        keyStrokeHandled = true;
//    }
//    return keyStrokeHandled;
//}

//bool BoundariesSprite::onMouseMove(Point p) {
//    r.position.x = p.x;
//    r.position.y = p.y;
//    return true;
//}

void BoundariesSprite::onRender(Graphics *g) {
    g->drawRect(r, color);
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
