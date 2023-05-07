#include <stdio.h>
#include "field.h"
#include "raylib.h"
#include "debugmalloc.h"

void ResetField(Field *f, int i, int j) {
    f->x = j;
    f->y = i;
    f->isMine = false;
    f->flagged = false;
    f->revealed = false;
    f->neighbourMineCount = 0;
    f->neighbourCount = 0;
}

void DrawField(Field *f, int x, int y, int width, int height) {
    Color color = GRAY;
    if (f->revealed) {
        if (f->isMine) {
            DrawRectangle(x, y, width, height, DARKGRAY);
            DrawText("B", x + 5, y + 5, 30, RED);
        } else if (f->neighbourMineCount == 0) DrawRectangle(x, y, width, height, DARKGRAY);
        else {
            DrawRectangle(x, y, width, height, DARKGRAY);
            char c[2];
            sprintf(c, "%d", f->neighbourMineCount);
            DrawText(c, x + 5, y + 5, 30, BLUE);
        }
    } else if (f->flagged) {
        DrawText("F", x + 5, y + 5, 30, YELLOW);
    }

}

Field *NewField(int i, int j) {
    Field *f = malloc(sizeof *f);
    f->neighbours = malloc(8 * sizeof *f->neighbours);
    ResetField(f, i, j);
    return f;
}

void RevealField(Field *f, gameState *state, int *flagCount, int *maxFields) {
    if (f->isMine) {
        f->revealed = true;
        *state = lost;
    } else if (!f->revealed && !f->flagged) {
        f->revealed = true;
        (*maxFields)--;
        //if (f->flagged) (*flagCount)--;
        if (*maxFields == 0) *state = won;
        else {
            if (f->neighbourMineCount == 0) {
                for (int i = 0; i < f->neighbourCount; i++) {
                    if (!f->neighbours[i]->isMine) RevealField(f->neighbours[i], state, flagCount, maxFields);
                }
            }
        }
    }
}

void FlagField(Field *f, int *count) {
    if (!f->revealed) {
        f->flagged = !f->flagged;
        (*count)++;
    };
}

void UnFlagField(Field *f, int *count) {
    (*count)--;
    f->flagged = !f->flagged;
}

/*void NeighbourCount(Table* t, Field* f){
    if(f->x>0){
        if(f->x<t->rows-1){
            if(f->y>0){
                if(f->y<t->columns-1){
                    for(int i=f->x-1;i<f->x+1;i++){
                        for(int j=f->y-1;j<f->y+1;j++){
                            if(t->fields[i][j].isMine) f->neighbourMineCount++;
                        }
                    }
                }else{
                    for(int i=f->x-1;i<f->x+1;i++){
                        for(int j=f->y-1;j<f->y;j++){
                            if(t->fields[i][j].isMine) f->neighbourMineCount++;
                        }
                    }
                }
            }else{
                for(int i=f->x-1;i<f->x+1;i++){
                    for(int j=f->y;j<f->y+1;j++){
                        if(t->fields[i][j].isMine) f->neighbourMineCount++;
                    }
                }
            }
        }else if(f->y>0){
            if(f->y<t->columns-1){
                for(int i=f->x-1;i<f->x;i++){
                    for(int j=f->y-1;j<f->y+1;j++){
                        if(t->fields[i][j].isMine) f->neighbourMineCount++;
                    }
                }
            }else{
                for(int i=f->x-1;i<f->x;i++){
                    for(int j=f->y-1;j<f->y;j++){
                        if(t->fields[i][j].isMine) f->neighbourMineCount++;
                    }
                }
            }
        }else{
            for(int i=f->x-1;i<f->x;i++){
                for(int j=f->y;j<f->y+1;j++){
                    if(t->fields[i][j].isMine) f->neighbourMineCount++;
                }
            }
        }

    }else if(f->y>0){
        if(f->y<t->columns-1){
            for(int i=f->x;i<f->x+1;i++){
                for(int j=f->y-1;j<f->y+1;j++){
                    if(t->fields[i][j].isMine) f->neighbourMineCount++;
                }
            }
        }else{
            for(int i=f->x;i<f->x+1;i++){
                for(int j=f->y-1;j<f->y;j++){
                    if(t->fields[i][j].isMine) f->neighbourMineCount++;
                }
            }
        }
    }else{
        for(int i=f->x;i<f->x+1;i++){
            for(int j=f->y;j<f->y+1;j++){
                if(t->fields[i][j].isMine) f->neighbourMineCount++;
            }
        }
    }
}*/

