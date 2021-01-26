//
//  Window.hpp
//  BSPAlgorithm
//
//  Created by Enrique on 1/23/21.
//

#ifndef Window_hpp
#define Window_hpp
#include <SDL2/SDL.h>
#include "Structs.h"

class Graphics;

class Window {
private:
    SDL_Surface *surface = NULL;
    SDL_Window *window = NULL;

    void initialize_window(void);
    void initialize_surface(void);
    void initialize_event_loop(void);
public:
    Window();
    ~Window();

    void show();
    Rect getFrame();
    Size getSize();
    Point getPosition();
    
    Graphics getGraphics();
};


#endif /* Window_hpp */
