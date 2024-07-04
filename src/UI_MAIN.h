#ifndef UIMAIN_H
#define UIMAIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
using namespace std;

class UI_MAIN {
public:
    UI_MAIN();
    ~UI_MAIN();
    bool initialize();
    SDL_Renderer* getRenderer() const;
    void runMainProgram(SDL_Renderer* renderer, int** playerBoard, int rows, int cols);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif