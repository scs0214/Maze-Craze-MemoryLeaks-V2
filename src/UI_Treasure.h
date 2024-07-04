#ifndef TREASUREUI_H
#define TREASUREUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

class UI_Treasure {
public:
    void renderTreasure(SDL_Renderer* renderer, int row, int col);
    void runWinScreen(SDL_Renderer* renderer, int winnerPlayer);
};

#endif