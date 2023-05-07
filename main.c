#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "table.h"
#include "startscreen.h"
#include "debugmalloc.h"


int main() {
    srand(time(NULL));
    const int screenWidth = 500;
    const int screenHeight = 500;
    const int fieldSize = 40;

    bool gameStarted = false;

    InitWindow(screenWidth, screenHeight, "Aknakereső");

    SetTargetFPS(60);

    bool shouldRun = true;
    StartScreen *startScreen = NewStartScreen();
    //malloc(300);

    while (shouldRun) {
        SetWindowSize(screenWidth, screenHeight);

        while (shouldRun && !gameStarted) {
            shouldRun = !WindowShouldClose();
            UpdateStartScreen(startScreen, &gameStarted);
            BeginDrawing();
            DrawStartScreen(startScreen);
            EndDrawing();

        }

        Table *t = NewTable(startScreen->tableWidth, startScreen->tableHeight, startScreen->mineCount, fieldSize);
        //ell(t);
        SetWindowSize(fieldSize * t->columns + 2, fieldSize * t->rows + 75 + 1);
        time_t start;
        time(&start);
        while (shouldRun && gameStarted) {
            shouldRun = !WindowShouldClose();
            UpdateTable(t, &gameStarted);
            BeginDrawing();
            DrawTable(t, &start);
            EndDrawing();
        }
        FreeTable(t);

    }
    FreeStartScreen(startScreen);
    CloseWindow();

    return 0;
}
