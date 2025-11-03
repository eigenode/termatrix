#include "termatrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// Global state (standard for TUI signal handling)
static Termatrix *g_tmx = NULL;
static char *g_framebuf = NULL;

void restore_terminal() {
    printf("\033[0m\033[?25h"); // Reset colors + show cursor
    fflush(stdout);
}

void handle_sigint(int sig) {
    printf("Received signal %d, exiting...\n", sig);
    exit(0);
}

void cleanup(void) {
    restore_terminal();

    if (g_framebuf) {
        free(g_framebuf);
        g_framebuf = NULL;
    }

    termatrix_destroy(g_tmx);
    g_tmx = NULL;
}


int main(void) {

    srand((unsigned)time(NULL));

    atexit(cleanup);
    signal(SIGINT, handle_sigint);

    g_tmx = termatrix_create();
    if (!g_tmx) {
        fprintf(stderr, "Failed to allocate terminal matrix.\n");
        exit(1);
    }

    termatrix_init(g_tmx);

    // Max bytes per cell: "\033[97m" (7 bytes) + char (1) = 8 bytes
    int bytes_per_cell = 8;
    size_t buffer_size = g_tmx->rows * (g_tmx->cols * bytes_per_cell + 1) + 16;
    char *buffer = malloc(buffer_size);

    printf("\033[2J\033[?25l");

    int frame = 0;
    while (1) {
        termatrix_update(g_tmx, frame++);
        termatrix_render(g_tmx, buffer);
        sleep_ms(30);
    }

    cleanup();
    return 0;
}
