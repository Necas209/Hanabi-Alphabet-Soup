#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include "cJSON.h"

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

cJSON *save_card(const card_t *card);

void load_card(cJSON *card_json, card_t *card);

#endif //CARD_H
