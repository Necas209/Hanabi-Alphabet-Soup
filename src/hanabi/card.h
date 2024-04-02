#ifndef CARD_H
#define CARD_H

#include <stdbool.h>
#include <stdio.h>
#include "../lib/cJSON.h"
#include "../lib/vec.h"

typedef enum color {
    YELLOW,
    BLUE,
    GREEN,
    RED,
    WHITE
} color_t;

#define INVALID_CARD UINT32_MAX

typedef struct card {
    int number;
    color_t color;
    bool number_known;
    bool color_known;
} card_t;

typedef vec_t(card_t) card_vec_t;

/// String representation of the colors
extern const char *colors[];

/// Get JSON object for a card vector
/// \param cards The card vector to get the JSON object for
/// \return The JSON object for the card vector
cJSON *get_card_vec_json(const card_vec_t *cards);

/// Load a card vector from a JSON object
/// \param cards_json The JSON object to load the card vector from
/// \return The loaded card vector
card_vec_t load_card_vec(const cJSON *cards_json);

/// Get JSON object for a card
/// \param card The card to get the JSON object for
/// \return The JSON object for the card
cJSON *get_card_json(const card_t *card);

/// Load a card from a JSON object
/// \param card_json The JSON object to load the card from
/// \return The loaded card
card_t load_card(const cJSON *card_json);

#endif //CARD_H
