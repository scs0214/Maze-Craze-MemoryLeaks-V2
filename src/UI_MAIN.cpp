#include "UI_ImageLoader.h"
#include "UI_Board.h"
#include "UI_MAIN.h"
#include <iostream>
using namespace std;

UI_Board uiBoard;

UI_MAIN::UI_MAIN() : window(nullptr), renderer(nullptr) {}

UI_MAIN::~UI_MAIN() {
    for (auto texture : imageLoader.textures) {
        SDL_DestroyTexture(texture);
    }
    imageLoader.textures.clear();

    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool UI_MAIN::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "No se pudo inicializar SDL: " << SDL_GetError() << ::endl;
        return false;
    }

    window = SDL_CreateWindow(
        "Maze Craze - Memory Leaks",
         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        cerr << "La ventana no pudo ser creada: " << SDL_GetError() << endl;
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cerr << "El renderizador no pudo ser creado: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        cerr << "SDL_image no pudo ser inicializado. IMG_Error: " << IMG_GetError() << endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf no pudo ser inicializado. TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    imageLoader.generatePathsForVector();
    imageLoader.loadImages(renderer, imageLoader.imagePaths);

    return true;
}

SDL_Renderer* UI_MAIN::getRenderer() const {
    return renderer;
}

void UI_MAIN::runMainProgram(SDL_Renderer* renderer, int** playerBoard, int rows, int cols) {
    SDL_RenderClear(renderer);

    uiBoard.renderBoard(renderer, playerBoard, rows, cols);

    SDL_RenderPresent(renderer);
}