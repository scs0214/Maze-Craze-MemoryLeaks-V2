#include "UI_Cell.h"
#include "UI_ImageLoader.h"
#include "UI_Treasure.h"
#include <iostream>
using namespace std;

void UI_Treasure::renderTreasure(SDL_Renderer* renderer, int row, int col) {         
    SDL_Rect treasure = {col * CELL_SIZE + BORDER_WIDTH, row * CELL_SIZE + BORDER_WIDTH, 
                          CELL_SIZE - 2 * BORDER_WIDTH, CELL_SIZE - 2 * BORDER_WIDTH};
            
    if (!imageLoader.textures.empty()) {
        SDL_RenderCopy(renderer, imageLoader.textures[7], nullptr, &treasure);
    }

    SDL_RenderPresent(renderer);
}

void UI_Treasure::runWinScreen(SDL_Renderer* renderer, int winnerPlayer) {
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, imageLoader.textures[8], nullptr, nullptr);

    SDL_RenderPresent(renderer);
}