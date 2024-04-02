#include "lab.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

// Set the foreground and background color
__attribute__((unused)) void setColor(const ansi_color_t foreground, const ansi_bg_color_t background) {
    printf("\033[%d;%dm", foreground, background);
}

// Set the foreground color
void setForeColor(const ansi_color_t foreground) {
    printf("\033[%dm", foreground);
}

// Reset the color
void resetColor() {
    printf("\033[0m");
}

// Move the cursor to a specific location
void gotoxy(const int x, const int y) {
    printf("\033[%d;%dH", y, x);
}

// Print a string horizontally at a specific location
void printfAt(const int x, const int y, const char c[], ...) {
    gotoxy(x, y);
    // Initialize the va_list
    va_list args;
    va_start(args, c);
    // Print the string
    vprintf(c, args);
}

// Draw a rectangle at a specific location
void showRectAt(const int x, const int y, const int width, const int height) {
    // Move the cursor to the starting position
    gotoxy(x, y);

    // Print the top border
    printf("%s", "╔"); // top left corner
    for (int i = 0; i < width - 2; i++) {
        printf("%s", "═"); // horizontal side
    }
    printf("%s\n", "╗"); // top right corner

    // Print the middle part
    for (int i = 0; i < height - 2; i++) {
        gotoxy(x, y + i + 1);
        printf("%s", "║"); // vertical side
        for (int j = 0; j < width - 2; j++) {
            printf(" "); // space
        }
        printf("%s\n", "║"); // vertical side
    }

    // Print the bottom border
    gotoxy(x, y + height - 1);
    printf("%s", "╚"); // bottom left corner
    for (int i = 0; i < width - 2; i++) {
        printf("%s", "═"); // horizontal side
    }
    printf("%s\n", "╝"); // bottom right corner
}

// Generate a random integer between lower and upper
uint32_t generate_random_int(const uint32_t lower, const uint32_t upper) {
    // Generate a random number between lower and upper (inclusive)
    const uint32_t num = lower + arc4random_uniform(upper - lower + 1);
    return num;
}

/* msleep(): Sleep for the requested number of milliseconds. */
int msleep(const uint32_t milliseconds) {
    struct timespec ts = {
            .tv_sec = milliseconds / 1000,
            .tv_nsec = milliseconds % 1000 * 1000000
    };

    int res;
    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}
