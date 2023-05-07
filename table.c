#include <stdlib.h>
#include "table.h"
#include "raylib.h"
#include <time.h>
#include <stdio.h>
#include "debugmalloc.h"

void FormatTime(double diftime, char *timeText) {
    int minutes = diftime / 60;
    int seconds = diftime - minutes * 60;
    char min[3];
    char sec[3];
    if (minutes < 10) {
        sprintf(&min, "0%d", minutes);
    } else sprintf(&min, "%d", minutes);

    if (seconds < 10) {
        sprintf(&sec, "0%d", seconds);
    } else sprintf(&sec, "%d", seconds);

    sprintf(timeText, "%s:%s", min, sec);
}

void DrawTable(Table *t, time_t *start) {
    double diftime;
    diftime = difftime(t->currentTime, *start);
    if (diftime > 99) start = 0;
    ClearBackground(RAYWHITE);
    for (int i = 0; i < t->rows; i++) {
        for (int j = 0; j < t->columns; j++) {
            int x = j * t->fieldSize + 1;
            int y = i * t->fieldSize + 75;
            DrawField(t->fields[i][j], x, y, t->fieldSize, t->fieldSize);
            DrawRectangleLines(x, y, t->fieldSize, t->fieldSize, BLACK);
        }
    }

    sprintf(t->flagText, "Flags: %d", t->bombs - t->flags);
    FormatTime(diftime, t->timeText);
    DrawText(t->timeText, 10, 10, 30, BLUE);
    DrawText(t->flagText, GetScreenWidth() - (MeasureText(t->flagText, 20) + 10), 10, 20, BLUE);
    if (t->state == won) {
        DrawText("You Won!", GetScreenWidth() / 2 - MeasureText("You Won!", 30) / 2, 10, 30, BLUE);
        DrawText("PRESS ENTER TO CONTINUE", GetScreenWidth() / 2 - MeasureText("PRESS ENTER TO CONTINUE", 10) / 2, 50,
                 10, BLUE);

    } else if (t->state == lost) {
        DrawText("You Lost!", GetScreenWidth() / 2 - MeasureText("You Won!", 30) / 2, 10, 30, RED);
        DrawText("PRESS ENTER TO CONTINUE", GetScreenWidth() / 2 - MeasureText("PRESS ENTER TO CONTINUE", 10) / 2, 50,
                 10, RED);
    }

}

int CountFieldNeighbourMines(Table *t, Field *f) {
    int count = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            int x = f->x + j;
            int y = f->y + i;
            if (x >= 0 && y >= 0 && x < t->columns && y < t->rows) {
                Field *neighbour = t->fields[y][x];
                if (neighbour->isMine) {
                    count++;
                }

            }
        }
    }
    return count;
}

void ResetTable(Table *t) {
    for (int i = 0; i < t->rows; i++) {
        for (int j = 0; j < t->columns; j++) {
            ResetField(t->fields[i][j], i, j);
        }
    }
    int maxBombs = t->columns * t->rows;
    int bombs = (t->bombs > maxBombs) ? maxBombs : t->bombs;
    while (bombs > 0) {
        int x = rand() % t->columns;
        int y = rand() % t->rows;
        if (!t->fields[y][x]->isMine) {
            t->fields[y][x]->isMine = true;
            bombs--;
        }
    }

    for (int i = 0; i < t->rows; i++) {
        for (int j = 0; j < t->columns; j++) {
            t->fields[i][j]->neighbourMineCount = CountFieldNeighbourMines(t, t->fields[i][j]);
        }
    }
}

Table *NewTable(const int columns, const int rows, int bombs, int fieldSize) {
    Table *t = malloc(sizeof *t);
    t->columns = columns;
    t->rows = rows;
    t->bombs = bombs;
    t->fieldSize = fieldSize;
    t->state = inGame;
    t->flags = 0;
    t->fieldsLeft = columns * rows - bombs;
    time(&t->currentTime);
    t->timeText = malloc(10 * sizeof *t->timeText);
    t->flagText = malloc(10 * sizeof *t->timeText);
    t->fields = malloc(rows * sizeof *t->fields);
    for (int i = 0; i < rows; i++) {
        t->fields[i] = malloc(columns * sizeof *t->fields[i]);
        for (int j = 0; j < columns; j++) {
            t->fields[i][j] = NewField(i, j);
        }
    }
    ResetTable(t);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            Field *currentField = t->fields[i][j];
            for (int k = -1; k < 2; k++) {
                for (int l = -1; l < 2; l++) {
                    int x = j + l;
                    int y = i + k;
                    if (x >= 0 && y >= 0 && x < t->columns && y < t->rows) {
                        Field *neighbour = t->fields[y][x];
                        if (neighbour != currentField)
                            currentField->neighbours[currentField->neighbourCount++] = neighbour;
                    }
                }
            }
        }
    }


    return t;
}

void UpdateTable(Table *t, bool *gameStarted) {
    /*int z = GetMouseX() / t->fieldSize;
    int u = GetMouseY() / t->fieldSize - 1;
    printf("%d %d\n", z, u);*/
    if (t->state == inGame) {
        time(&t->currentTime);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();
            if (mouseX >= 0 && mouseY >= 75 && mouseX < t->columns * t->fieldSize &&
                mouseY < t->rows * t->fieldSize + 75) {
                int x = mouseX / t->fieldSize;
                int y = (mouseY - 75) / t->fieldSize;
                //printf("%d %d\n", x, y);
                RevealField(t->fields[y][x], &t->state, &t->flags, &t->fieldsLeft);
            }
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {

            int mouseX = GetMouseX();
            int mouseY = GetMouseY();
            if (mouseX >= 0 && mouseY >= 75 && mouseX < t->columns * t->fieldSize &&
                mouseY < t->rows * t->fieldSize + 75) {
                int x = mouseX / t->fieldSize;
                int y = (mouseY - 75) / t->fieldSize;
                //printf("%d %d\n", x, y);
                if (!t->fields[y][x]->flagged && t->flags < t->bombs) FlagField(t->fields[y][x], &t->flags);
                else if (t->fields[y][x]->flagged) UnFlagField(t->fields[y][x], &t->flags);
            }

        }
    }
    if (IsKeyPressed(KEY_ENTER) && (t->state == won || t->state == lost)) {
        *gameStarted = false;
    }
}

void FreeTable(Table *t) {
    for (int i = 0; i < t->rows; i++) {
        for (int j = 0; j < t->columns; j++) {
            free(t->fields[i][j]->neighbours);
            free(t->fields[i][j]);
        }
        free(t->fields[i]);
    }
    free(t->fields);
    free(t->timeText);
    free(t->flagText);
    free(t);
}

void ell(Table *t) {
    for (int i = 0; i < t->rows; i++) {
        for (int j = 0; j < t->columns; j++) {
            printf("%d ", t->fields[i][j]->isMine);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < t->rows; i++) {
        for (int j = 0; j < t->columns; j++) {
            printf("%d ", t->fields[i][j]->neighbourMineCount);
        }
        printf("\n");
    }
}
