//
//  UI.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 4/29/21.
//

#include "UI.h"

#include <SDL2/SDL.h>

#include "../ImGUISDL/include/imgui.h"
#if defined(__APPLE__) && defined(__MACH__)
#include "../ImGUISDL/include/imgui_sdl.h"
#else
#include "../ImGUISDL/include/imgui_impl_sdl.h"
#include "../ImGUISDL/include/imgui_impl_sdlrenderer.h"
#endif
//

#include <sstream>
#include <random>
#include <algorithm>
#include <cassert>
#include <cstdarg>

namespace UniqueIdentifier {
    unsigned int random_char() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 255);
        return dis(gen);
    }

    std::string generate_hex(const unsigned int len) {
        std::stringstream ss;
        for (auto i = 0; i < len; i++) {
            const auto rc = random_char();
            std::stringstream hexstream;
            hexstream << std::hex << rc;
            auto hex = hexstream.str();
            ss << (hex.length() < 2 ? '0' + hex : hex);
        }
        return ss.str();
    }
}

UI::UI() {
#if defined(__APPLE__) && defined(__MACH__)
    IMGUI_CHECKVERSION();
#endif
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
}

UI::~UI() {
#if defined(__APPLE__) && defined(__MACH__)
    ImGuiSDL::Deinitialize();
#else
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
#endif
    ImGui::DestroyContext();
}

void UI::initialize(SDL_Window* window, SDL_Renderer* renderer, Size s) {
    this->window = window;
    ImGui::CreateContext();
#if defined(__APPLE__) && defined(__MACH__)
    ImGuiSDL::Initialize(renderer, s.width, s.height);
#else
    ImGui_ImplSDL2_InitForSDLRenderer(window);
    ImGui_ImplSDLRenderer_Init(renderer);
#endif    
}

void UI::getUserInputHandler() {
    this->io = &ImGui::GetIO();
}

void UI::refresh() {
    assert(frames.size() == 0);
    ImGui::Render();
#if defined(__APPLE__) && defined(__MACH__)
    ImGuiSDL::Render(ImGui::GetDrawData());
#else
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
#endif    
}

void UI::showDemoScreen() {
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();
    ImGui::EndFrame();
}

UIFrameContext UI::BeginFrame(const char* name) {
    UIFrameContext context = UniqueIdentifier::generate_hex(16);
    frames.push_back(context);
#if defined(__APPLE__) && defined(__MACH__)
#else
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame(this->window);
#endif
    ImGui::NewFrame();
    ImGui::Begin(name, NULL, ImGuiWindowFlags_AlwaysAutoResize);
    
    return context;
}

void UI::CreateText(UIFrameContext context, const char* fmt, ...) {
    auto it = std::find(frames.begin(), frames.end(), context);
    assert(it != frames.end());
    va_list args;
    va_start(args, fmt);
    ImGui::TextV(fmt, args);
    va_end(args);
}

void UI::EndFrame(UIFrameContext context) {
    auto it = std::find(frames.begin(), frames.end(), context);
    frames.erase(it);
    ImGui::End();
    ImGui::EndFrame();
}
