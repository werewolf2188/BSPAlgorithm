//
//  UI.cpp
//  BSPAlgorithm
//
//  Created by Enrique on 4/29/21.
//

#include "UI.h"

#include <SDL2/SDL.h>

#include "../ImGUISDL/include/imgui.h"
#include "../ImGUISDL/include/imgui_sdl.h"

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
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
}

UI::~UI() {
    ImGuiSDL::Deinitialize();
    ImGui::DestroyContext();
}

void UI::initialize(SDL_Renderer* renderer, Size s) {
    ImGui::CreateContext();
    ImGuiSDL::Initialize(renderer, s.width, s.height);
}

void UI::getUserInputHandler() {
    this->io = &ImGui::GetIO();
}

void UI::refresh() {
    assert(frames.size() == 0);
    ImGui::Render();
    ImGuiSDL::Render(ImGui::GetDrawData());
}

void UI::showDemoScreen() {
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();
    ImGui::EndFrame();
}

UIFrameContext UI::BeginFrame(const char* name) {
    UIFrameContext context = UniqueIdentifier::generate_hex(16);
    frames.push_back(context);
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
