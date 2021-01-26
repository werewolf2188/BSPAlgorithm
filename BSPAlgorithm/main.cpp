//
//  main.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 1/23/21.
//

#include <iostream>
#include "Classes/Window.h"
#include "Classes/Graphics.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    GameLoop gameLoop;
    Window w(&gameLoop);
//    Graphics g = w.getGraphics();
//    g.drawLine({ 100, 100 }, { 300, 200} , RED); //DIAGONAL
//    g.drawLine({ 100, 100 }, { 100, 300} , GREEN); //VERTICAL
//    g.drawLine({ 100, 100 }, { 300, 100} , BLUE); //HORIZONTAL
//    g.drawRect({{ 1200, 800}, {50, 50}}, BLACK);
//    g.drawCircle({ 500, 500 }, 50, BLACK);
//    g.drawDisk({ 700, 500 }, 50, BLACK);
//    g.update();
//    g.clear();
    w.show();
    return 0;
}
