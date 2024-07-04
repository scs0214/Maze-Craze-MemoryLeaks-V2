#include "UI_ImageLoader.h"
#include <iostream>
using namespace std;

UI_ImageLoader imageLoader;

void UI_ImageLoader::generatePathsForVector() {
    imagePaths.push_back("ui files/titlebg.png"); // Position in vector: 0
    imagePaths.push_back("ui files/player1.png"); // Position in vector: 1
    imagePaths.push_back("ui files/player2.png"); // Position in vector: 2
    imagePaths.push_back("ui files/DoubleTurnCell.png"); // Position in vector: 3
    imagePaths.push_back("ui files/MindControlCell.png"); // Position in vector: 4
    imagePaths.push_back("ui files/JumpWallCell.png"); // Position in vector: 5
    imagePaths.push_back("ui files/PortalCell.png"); // Position in vector: 6
    imagePaths.push_back("ui files/TreasureCell.png"); // Position in vector: 7
    imagePaths.push_back("ui files/winscreen.png"); // Position in vector: 8
}

bool UI_ImageLoader::loadImages(SDL_Renderer* renderer, const vector<string>& paths) {
    for (const auto& path : paths) {
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        if (!loadedSurface) {
            cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << endl;
            return false;
        }
        SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
        if (!newTexture) {
            cerr << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << endl;
            return false;
        }
        textures.push_back(newTexture);
    }
    return true;
}  