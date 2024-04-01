#ifndef HAND_H
#define HAND_H

#include "card.h"

#define NAME 16
#define HAND_LEN 5

typedef struct hand {
    card_t cards[HAND_LEN];
    char name[NAME];
} hand_t;

int lowest_unknown_number(const hand_t *hand);

color_t random_unknown_color(const hand_t *hand);

int cards_with_color(const hand_t *hand, color_t color);

int cards_with_number(const hand_t *hand, int number);

void give_number_clue(const hand_t *from, hand_t *to, int number);

void give_color_clue(const hand_t *from, hand_t *to, color_t color);

cJSON *get_hand_json(const hand_t *hand);

void load_hand(cJSON *hand_json, hand_t *hand);

#endif //HAND_H
