#ifndef BOARDUI_H
#define BOARDUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

class UI_Board {
public:
    void renderBoard(SDL_Renderer* renderer, int** playerBoard, int rowAmount, int colAmount);
};

#endif