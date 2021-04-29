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
#include "GameLoop.h"

class Graphics;

class Window {
private:
    SDL_Surface *surface = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
    GameLoop *gameLoop;

    void initialize_window(void);
    void initialize_graphics(void);
    void initialize_event_loop(void);
public:
    Window(GameLoop* gameLoop);
    ~Window();

    void show();
    Rect getFrame();
    Size getSize();
    Point getPosition();
    
    Graphics* getGraphics();
};


#endif /* Window_hpp */
