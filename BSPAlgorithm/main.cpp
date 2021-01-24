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
    Window w;
    Graphics* g = w.getGraphics();
    g->drawPoint({ 100, 100 }, BLACK);
    w.show();
    delete g;
    return 0;
}
