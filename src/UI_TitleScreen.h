#ifndef UI_TITLESCREEN_H
#define UI_TITLESCREEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std;

class UI_TitleScreen {
public:
    void runTitleScreen(SDL_Renderer* renderer);
    bool buttonClick(SDL_Event& event);
};

#endif