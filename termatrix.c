#include "termatrix.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <time.h>

int randint(int min, int max) {
    return rand() % (max + 1 - min) + min;
}

Termatrix* termatrix_create() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    Termatrix *tmx = malloc(sizeof(Termatrix));
    tmx->rows = w.ws_row;
    tmx->cols = w.ws_col;

    tmx->grid = malloc(tmx->rows * tmx->cols);
    tmx->head_positions = malloc(sizeof(int) * tmx->cols);
    tmx->trail_lengths = malloc(sizeof(int) * tmx->cols);
    tmx->fall_speeds = malloc(sizeof(int) * tmx->cols);

    return tmx;
}

size_t termatrix_pos(Termatrix *tmx, int row, int col) {
    return row * tmx->cols + col;
}

void termatrix_init(Termatrix *tmx) {
    // Clear grid
    for (int r = 0; r < tmx->rows; r++)
        for (int c = 0; c < tmx->cols; c++)
            tmx->grid[termatrix_pos(tmx, r, c)] = ' ';

    // Randomized rain config
    for (int c = 0; c < tmx->cols; c++) {
        tmx->head_positions[c] = randint(0, tmx->rows - 1);
        tmx->trail_lengths[c] = randint(5, tmx->rows / 2);
        tmx->fall_speeds[c] = randint(1, 4);
    }
}

void termatrix_update(Termatrix *tmx, int frame_count) {
    for (int c = 0; c < tmx->cols; c++) {

        if (frame_count % tmx->fall_speeds[c] != 0)
            continue;

        int head = (tmx->head_positions[c] + 1) % tmx->rows;
        tmx->head_positions[c] = head;
        tmx->grid[termatrix_pos(tmx, head, c)] = (char)randint(33, 126);
    }
}

void termatrix_render(Termatrix *tmx, char *buffer) {
    char *p = buffer;
    p += sprintf(p, "\033[H");

    for (int r = 0; r < tmx->rows; r++) {
        for (int c = 0; c < tmx->cols; c++) {
            char ch = tmx->grid[termatrix_pos(tmx, r, c)];
            int head = tmx->head_positions[c];
            int trail_len = tmx->trail_lengths[c];
            int dist = (head - r + tmx->rows) % tmx->rows;

            if (dist == 0)
                p += sprintf(p, "\033[97m%c", ch);
            else if (dist < trail_len / 3)
                p += sprintf(p, "\033[92m%c", ch);
            else if (dist < trail_len)
                p += sprintf(p, "\033[32m%c", ch);
            else
                p += sprintf(p, "\033[0m ");
        }
        *p++ = '\n';
    }

    *p = '\0';
    fwrite(buffer, 1, p - buffer, stdout);
    fflush(stdout);
}

void termatrix_destroy(Termatrix *tmx) {
    free(tmx->grid);
    free(tmx->head_positions);
    free(tmx->trail_lengths);
    free(tmx->fall_speeds);
    free(tmx);
}

void sleep_ms(int ms) {
    struct timespec ts = {
        .tv_sec = ms / 1000,
        .tv_nsec = (ms % 1000) * 1000000L
    };
    nanosleep(&ts, NULL);
}
