#ifndef CARD_H
#define CARD_H

#include <stdio.h>

typedef enum color {
    YELLOW,
    BLUE,
    GREEN,
    RED,
    WHITE
} color_t;

typedef struct card {
    int number;
    color_t color;
    bool number_known;
    bool color_known;
} card_t;

extern const char *colors[];

// Function Prototypes

void save_card(FILE *file, const card_t *card);

void load_card(FILE *file, card_t *card);

#endif //CARD_H
