//
//  UI.hpp
//  BSPAlgorithm
//
//  Created by Enrique on 4/29/21.
//

#ifndef UI_hpp
#define UI_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "Structs.h"

typedef std::string UIFrameContext;

struct SDL_Renderer;
struct SDL_Window;
struct ImGuiIO;
//
// The library needs to be in /usr/local/lib/
// either create a runtime phase to copy the library or <-- Done
// change the reference to not look in that library

class UI {
private:
    ImGuiIO* io;
    SDL_Window* window;
    std::vector<UIFrameContext> frames;
public:
    UI();
    ~UI();

    void initialize(SDL_Window* window, SDL_Renderer* renderer, Size s);
    void getUserInputHandler();
    void showDemoScreen();
    void refresh();

    UIFrameContext BeginFrame(const char* name);
    void CreateText(UIFrameContext context, const char* fmt, ...);
    void EndFrame(UIFrameContext context);
};

#endif /* UI_hpp */
