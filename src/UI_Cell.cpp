#include "UI_ImageLoader.h"
#include "UI_Cell.h"
#include <iostream>
using namespace std;

UI_Cell::UI_Cell() : texture(nullptr), positionX(0), positionY(0) {}

UI_Cell::~UI_Cell() {
    if (texture) SDL_DestroyTexture(texture);
    SDL_Quit();
}

void UI_Cell::renderCell(SDL_Renderer* renderer, int row, int col) { // Añadir 'int num' a los argumentos si existe una imagen para la celda
    SDL_Color borderColor = {0, 0, 0, 255};
    SDL_Color fillColor = {255, 255, 255, 255};

    SDL_Rect cell = {col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE};
            
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderFillRect(renderer, &cell);
            
    SDL_Rect innerCell = {col * CELL_SIZE + BORDER_WIDTH, row * CELL_SIZE + BORDER_WIDTH, 
                          CELL_SIZE - 2 * BORDER_WIDTH, CELL_SIZE - 2 * BORDER_WIDTH};
    SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
    SDL_RenderFillRect(renderer, &innerCell);
            
    // if (!imageLoader.textures.empty()) { 
        // SDL_RenderCopy(renderer, imageLoader.textures[num], nullptr, &innerCell);
    // }

    SDL_RenderPresent(renderer);
}