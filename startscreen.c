#include "startscreen.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
//#include "debugmalloc.h" //valamiert ez a resz nem tetszik a debugmallocnak es kifagy vele, valoszinuleg az sprintf miatt, de hogy miert? azt a debugmalloc tudja csak (valoszinuleg nem kompatibilis a raylibbel)

#define MIN_TABLE_HEIGHT 5
#define MAX_TABLE_HEIGHT 20
#define MIN_TABLE_WIDTH 5
#define MAX_TABLE_WIDTH 20
#define MIN_BOMB_COUNT 1
#define MAX_BOMB_COUNT 400

StartScreen *NewStartScreen() {

    FILE *settings = fopen("settings.ini", "r");
    StartScreen *startScreen = malloc(sizeof *startScreen);
    if (settings) {
        char *tmp = malloc(50 * sizeof *tmp);

        fscanf(settings, "%s %d", tmp, &startScreen->tableHeight);
        fscanf(settings, "%s %d", tmp, &startScreen->tableWidth);
        fscanf(settings, "%s %d", tmp, &startScreen->mineCount);
        free(tmp);
        fclose(settings);
    } else {
        startScreen->tableHeight = 10;
        startScreen->tableWidth = 10;
        startScreen->mineCount = 10;

    }
    startScreen->tableHeightText = malloc(50 * sizeof *startScreen->tableHeightText);
    startScreen->tableWidthText = malloc(50 * sizeof *startScreen->tableWidthText);
    startScreen->mineCountText = malloc(50 * sizeof *startScreen->mineCountText);
}


void UpdateStartScreen(StartScreen *startScreen, bool *gameStarted) {

    if (IsKeyPressed(KEY_ENTER)) {
        FILE *settings = fopen("settings.ini", "w+");
        if (settings) {
            fprintf(settings, "TableHeight: %d\n", startScreen->tableHeight);
            fprintf(settings, "TableWidth: %d\n", startScreen->tableWidth);
            fprintf(settings, "BombCount: %d\n", startScreen->mineCount);
            fclose(settings);
        }
        *gameStarted = true;
    }


    if (startScreen->tableHeight < MAX_TABLE_HEIGHT && IsKeyPressed(KEY_UP)) {
        startScreen->tableHeight++;
    }
    if (startScreen->tableHeight > MIN_TABLE_HEIGHT && IsKeyPressed(KEY_DOWN)) {
        startScreen->tableHeight--;
    }


    if (startScreen->tableWidth < MAX_TABLE_WIDTH && IsKeyPressed(KEY_RIGHT)) {
        startScreen->tableWidth++;
    }
    if (startScreen->tableWidth > MIN_TABLE_WIDTH && IsKeyPressed(KEY_LEFT)) {
        startScreen->tableWidth--;
    }


    if (startScreen->mineCount < MAX_BOMB_COUNT && IsKeyPressed(KEY_W)) {
        startScreen->mineCount++;
    }
    if (startScreen->mineCount > MIN_BOMB_COUNT && IsKeyPressed(KEY_S)) {
        startScreen->mineCount--;
    }

    sprintf(startScreen->tableWidthText, "Table Width: %d", startScreen->tableWidth);
    sprintf(startScreen->tableHeightText, "Table Height: %d", startScreen->tableHeight);
    sprintf(startScreen->mineCountText, "Number of Mines: %d", startScreen->mineCount);


}


void DrawStartScreen(StartScreen *startScreen) {
    ClearBackground(RAYWHITE);
    DrawText("Minesweeper", GetScreenWidth() / 2 - MeasureText("Minesweeper", 30) / 2, 10, 30, BLUE);
    DrawText(startScreen->tableHeightText, 30, 100, 30, BLUE);
    DrawText(startScreen->tableWidthText, 30, 175, 30, BLUE);
    DrawText(startScreen->mineCountText, 30, 250, 30, BLUE);
    DrawText("Change the Height with Up/Down Arrows", 10, GetScreenHeight() - 50, 10, BLUE);
    DrawText("Change the Width with Left/Right Arrows", 10, GetScreenHeight() - 40, 10, BLUE);
    DrawText("Change the Number of Mines with W/S", 10, GetScreenHeight() - 30, 10, BLUE);
}

void FreeStartScreen(StartScreen *startScreen) {
    free(startScreen->tableHeightText);
    free(startScreen->tableWidthText);
    free(startScreen->mineCountText);
    free(startScreen);
}

