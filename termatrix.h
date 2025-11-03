#ifndef TERMATRIX_H
#define TERMATRIX_H

#include <stddef.h>

typedef struct {
    int rows;
    int cols;
    char *grid;

    int *head_positions;
    int *trail_lengths;
    int *fall_speeds;
} Termatrix;

Termatrix* termatrix_create();
void termatrix_init(Termatrix *tmx);

size_t termatrix_pos(Termatrix *tmx, int row, int col);
void termatrix_update(Termatrix *tmx, int frame_count);
void termatrix_render(Termatrix *tmx, char *buffer);
void termatrix_destroy(Termatrix *tmx);

int randint(int min, int max);
void sleep_ms(int ms);

#endif