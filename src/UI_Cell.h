#ifndef CELLUI_H
#define CELLUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
const int CELL_SIZE = 50;
#define BORDER_WIDTH 2
using namespace std;

class UI_Cell {
public:
    UI_Cell();
    ~UI_Cell();
    void renderCell(SDL_Renderer* renderer, int row, int col);

private:
    SDL_Texture* texture;
    int positionX;
    int positionY;
};

#endif