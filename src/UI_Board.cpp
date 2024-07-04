#include "UI_ImageLoader.h"
#include "UI_Board.h"
#include "UI_Cell.h"
#include "UI_Power.h"
#include "UI_Player.h"
#include <iostream>
using namespace std;

UI_Cell uiCell;
UI_Power uiPower;
UI_Player uiPlayer;

void UI_Board::renderBoard(SDL_Renderer* renderer, int** playerBoard, int rowAmount, int colAmount) {
    for (int i = 0; i < rowAmount; i++) {
       for (int j = 0; j < colAmount; j++) {
            uiCell.renderCell(renderer, i, j);
            if (playerBoard[i][j] == 3) { // Double Turn
                uiPower.renderPower(renderer, i, j, 3);
            }
            else if (playerBoard[i][j] == 4) { // Mind Control
                uiPower.renderPower(renderer, i, j, 4);
            }
            else if (playerBoard[i][j] == 5) { // Jump Wall
                uiPower.renderPower(renderer, i, j, 5);
            }
            else if (playerBoard[i][j] == 6) { // Portal
                uiPower.renderPower(renderer, i, j, 6);
            }
            else if (playerBoard[i][j] == 7) { // Treasure
                uiPower.renderPower(renderer, i, j, 7);
            }
            else if (playerBoard[i][j] == 1 || playerBoard[i][j] == 2) { // Players (may move it to UI_Board)
                uiPlayer.renderPlayer(renderer, i, j, playerBoard[i][j]);
            }
        } 
    }

    SDL_RenderPresent(renderer);
}