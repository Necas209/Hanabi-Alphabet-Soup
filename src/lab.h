#ifndef _LABH_
#define _LABH_

#include <stdint.h>

typedef enum {
    ANSI_COLOR_BLACK = 30,
    ANSI_COLOR_RED,
    ANSI_COLOR_GREEN,
    ANSI_COLOR_YELLOW,
    ANSI_COLOR_BLUE,
    ANSI_COLOR_MAGENTA,
    ANSI_COLOR_CYAN,
    ANSI_COLOR_WHITE = 39,
} AnsiColor;

typedef enum {
    ANSI_BACKGROUND_BLACK = 40,
    ANSI_BACKGROUND_RED,
    ANSI_BACKGROUND_GREEN,
    ANSI_BACKGROUND_YELLOW,
    ANSI_BACKGROUND_BLUE,
    ANSI_BACKGROUND_MAGENTA,
    ANSI_BACKGROUND_CYAN,
    ANSI_BACKGROUND_WHITE
} AnsiBackgroundColor;

#ifdef __GNUC__
#define PRINTFLIKE(n,m) __attribute__((format(printf,n,m)))
#define NORETURN()      __attribute__((noreturn))
#else
#define PRINTFLIKE(n,m) /* If only */
#define NORETURN()      /* If only */
#endif /* __GNUC__ */

// Function prototypes

// Set the text color
void setForeColor(AnsiColor foreGround);

// Set the background color
void setColor(AnsiColor foreGround, AnsiBackgroundColor backGround);

// Reset the color
void resetColor();

// Move the cursor to a specific location
void gotoxy(int x, int y);

// Print a string horizontally at a specific location
void printfAt(int x, int y, const char c[], ...) PRINTFLIKE(3, 4);

// Draw a rectangle at a specific location
void showRectAt(int x, int y, int width, int height);

// Generate a random integer between lower and upper
uint32_t generate_random_int(uint32_t lower, uint32_t upper);

// Sleep for a number of milliseconds
int msleep(uint32_t milliseconds);

#endif
