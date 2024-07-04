#ifndef UI_IMAGELOADER_H
#define UI_IMAGELOADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
using namespace std;

class UI_ImageLoader {
public: 
    vector<SDL_Texture*> textures;
    vector<string> imagePaths;
    void generatePathsForVector();
    bool loadImages(SDL_Renderer* renderer, const vector<string>& paths);
};

extern UI_ImageLoader imageLoader;

#endif