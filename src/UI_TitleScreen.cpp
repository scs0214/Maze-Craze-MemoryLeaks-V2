#include "UI_ImageLoader.h"
#include "UI_TitleScreen.h"
#include <iostream>
using namespace std;

void UI_TitleScreen::runTitleScreen(SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, imageLoader.textures[0], nullptr, nullptr);

    int buttonWidth = 500;
    int buttonHeight = 100;

    SDL_Rect playButton = {(1280-buttonWidth)/2, 550, buttonWidth, buttonHeight};
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &playButton);

    SDL_RenderPresent(renderer);
}

bool isPointInRect(int x, int y, SDL_Rect rect) {
    return x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h;
}

bool UI_TitleScreen::buttonClick(SDL_Event& event) {
    bool returnValue = false;

    int buttonWidth = 500;
    int buttonHeight = 100;

    SDL_Rect playButton = {(1280-buttonWidth)/2, 550, buttonWidth, buttonHeight};

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        if (isPointInRect(x, y, playButton)) {
            returnValue = true;
        }
    }
    return returnValue;
}


