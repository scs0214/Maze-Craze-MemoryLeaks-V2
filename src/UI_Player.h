#ifndef PLAYERUI_H
#define PLAYERUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

class UI_Player {
public:
    UI_Player();
    void renderPlayer(SDL_Renderer* renderer, int row, int col, int num);
    char processInputP1(char& direction);
    char processInputP2(char& direction);
    void setPosition(int rowBackend, int colBackend);
    void setJumpWallAmount(int jwAmountBackend);
    int getJumpWallAmount() const;

private:
    int positionX;
    int positionY;
    int jumpWallAmount;
};

#endif