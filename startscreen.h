#ifndef MINESWEEPER_STARTSCREEN_H
#define MINESWEEPER_STARTSCREEN_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct StartScreen {
    int tableWidth, tableHeight, mineCount;
    char *tableWidthText, *tableHeightText, *mineCountText;
} StartScreen;

StartScreen *NewStartScreen();

void FreeStartScreen(StartScreen *startScreen);

void DrawStartScreen();

void UpdateStartScreen(StartScreen *startScreen, bool *gameStarted);


#endif //MINESWEEPER_STARTSCREEN_H
