#ifndef DECK_H
#define DECK_H

#define NUMBERS 5
#define COLORS 5
#define NUMBERS_PER_COLOR 10
#define DECK_LEN 50 // NUMBERS_PER_COLOR * COLORS

#include <stddef.h>
#include <stdint.h>

#include "hand.h"

typedef struct deck {
    card_t cards[DECK_LEN];
    size_t length;
    int discard_deck[NUMBERS][COLORS];
    int fireworks[COLORS];
} deck_t;

hand_t new_hand(deck_t *deck, const char *name);

bool play_card(deck_t *deck, hand_t *hand, uint32_t idx);

bool discard_card(deck_t *deck, hand_t *hand, uint32_t idx);

bool is_playable(const deck_t *deck, card_t card);

deck_t new_deck();

void shuffle_deck(deck_t *deck);

card_t draw_card(deck_t *deck);

int get_score(const deck_t *deck);

int get_lowest_table(const deck_t *deck);

bool is_table(const deck_t *deck);

cJSON *get_deck_json(const deck_t *deck);

void load_deck(cJSON *deck_json, deck_t *deck);

#endif //DECK_H
