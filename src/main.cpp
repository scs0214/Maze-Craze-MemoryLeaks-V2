#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "UI_MAIN.h"
#include "UI_TitleScreen.h"
#include "UI_Treasure.h"
#include "UI_Player.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    enum GameState {
        TITLE_SCREEN, MAIN_PROGRAM, WIN_SCREEN
    };

    {
        UI_MAIN uiMain;
        UI_TitleScreen uiTitleScreen;
        UI_Treasure uiWinScreen;
        UI_Player uiPlayer;


        if (!uiMain.initialize()) {
            cerr << "Failed to initialize UI_MAIN." << endl;
            return -1;
        }

        GameState currentGameState = TITLE_SCREEN; // Declares variables needed by the main program to create loops and render the different game stages
        SDL_Renderer* renderer = uiMain.getRenderer();
        SDL_Event event;
        bool running = true;
        char direction = 'x'; 
        int playerTurn = 1;

        int rowTest = 5;
        int colTest = 5;
        int** testMatrix = new int*[rowTest]; 
        for (int i = 0; i < rowTest; i++) {
            testMatrix[i] = new int[colTest];
        }

        testMatrix[0][0] = 1;
        testMatrix[1][3] = 3;
        testMatrix[4][3] = 4;
        testMatrix[3][0] = 5;
        testMatrix[1][4] = 6;
        testMatrix[2][2] = 7;

        while (running) {
            // Renderer Section (renders the different GameStates)
            if (currentGameState == TITLE_SCREEN) {
                uiTitleScreen.runTitleScreen(renderer);
            } else if (currentGameState == MAIN_PROGRAM) {
                // Initialize Backend
                uiMain.runMainProgram(renderer, testMatrix, rowTest, colTest);
            }
            else if (currentGameState == WIN_SCREEN) {
                uiWinScreen.runWinScreen(renderer, 1);
            }
        
            // Event Handler Section (handles different events to switch between GameStates)
            while (SDL_PollEvent(&event) != 0) {
                if (event.type == SDL_QUIT) {
                    running = false;
                }

                if (currentGameState == TITLE_SCREEN) {
                    if (uiTitleScreen.buttonClick(event)) {
                        currentGameState = MAIN_PROGRAM;
                    }
                } 
                
                else if (currentGameState == MAIN_PROGRAM) {
                    while(direction == 'x') {
                        if (playerTurn == 1) {
                            direction = uiPlayer.processInputP1(direction);
                        }
                        else if (playerTurn == 2) {
                            direction = uiPlayer.processInputP2(direction);
                        }
                        // Backend changes
                    }
                    direction = 'x';
                    currentGameState = WIN_SCREEN; // Include IF Win Condition
                }

                else if (currentGameState == WIN_SCREEN) {
                    SDL_Delay(5000);
                    running = false;
                }
            }
        }
        // All SDL processes are closed
    }

    return 0;
}
