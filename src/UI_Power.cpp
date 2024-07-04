#include "UI_Cell.h"
#include "UI_ImageLoader.h"
#include "UI_Power.h"
#include <iostream>
using namespace std;

UI_Power::UI_Power() : texture(nullptr), positionX(0), positionY(0) {}

UI_Power::~UI_Power() {
    if (texture) SDL_DestroyTexture(texture);
    SDL_Quit();
}

void UI_Power::renderPower(SDL_Renderer* renderer, int row, int col, int num) {         
    SDL_Rect powerForCell = {col * CELL_SIZE + BORDER_WIDTH, row * CELL_SIZE + BORDER_WIDTH, 
                          CELL_SIZE - 2 * BORDER_WIDTH, CELL_SIZE - 2 * BORDER_WIDTH};
            
    if (!imageLoader.textures.empty()) {
        SDL_RenderCopy(renderer, imageLoader.textures[num], nullptr, &powerForCell);
    }

    SDL_RenderPresent(renderer);
}