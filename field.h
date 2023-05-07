#ifndef MINESWEEPER_FIELD_H
#define MINESWEEPER_FIELD_H

#include <stdbool.h>

typedef enum gameState {
    won, lost, inGame
} gameState;

typedef struct Field {
    int x, y, neighbourMineCount;
    struct Field **neighbours;
    int neighbourCount;
    bool revealed, isMine, flagged;
} Field;

Field *NewField(int i, int j);

void ResetField(Field *f, int i, int j);

void DrawField(Field *f, int x, int y, int width, int height);

void RevealField(Field *f, gameState *state, int *flagCount, int *maxFields);

void FlagField(Field *f, int *count);

void UnFlagField(Field *f, int *count);

#endif //MINESWEEPER_FIELD_H
