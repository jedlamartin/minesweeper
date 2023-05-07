#ifndef MINESWEEPER_TABLE_H
#define MINESWEEPER_TABLE_H

#include "field.h"


typedef struct Table {
    int columns, rows, fieldSize, bombs, flags, fieldsLeft;
    gameState *state;
    time_t currentTime;
    char *timeText, *flagText;
    Field ***fields;
} Table;

void DrawTable(Table *t, time_t *start);

void ResetTable(Table *t);

Table *NewTable(const int columns, const int rows, int bombs, int fieldSize);

void UpdateTable(Table *t, bool *gameStarted);

void FreeTable(Table *t);

void ell(Table *t);

#endif //MINESWEEPER_TABLE_H
