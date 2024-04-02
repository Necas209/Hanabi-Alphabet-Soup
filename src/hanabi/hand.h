#ifndef HAND_H
#define HAND_H

#include "card.h"
#include "../lib/vec.h"

#define NAME 16
#define HAND_LEN 5

#define optional_type(type) struct { bool present; type value; }

typedef optional_type(card_t) optional_card_t;
typedef vec_t(color_t) color_vec_t;

typedef struct hand {
    card_vec_t cards;
    char name[NAME];
} hand_t;

/// Creates a new hand.
/// \param cards The cards in the hand. Must be of length HAND_LEN.
/// \param name The name of the hand. Must be of length NAME or less.
/// \return The hand.
hand_t new_hand(const card_t cards[HAND_LEN], const char *name);

/// Frees the hand.
/// \param hand The hand.
void free_hand(hand_t *hand);

/// Gets the number of cards in the hand.
/// \param hand The hand.
/// \return The number of cards in the hand.
int hand_len(const hand_t *hand);

/// Gets the lowest unknown number in the hand.
/// \param hand The hand.
/// \return The lowest unknown number in the hand, or -1 if all numbers are known.
int lowest_unknown_number(const hand_t *hand);

/// Gets a random unknown color in the hand.
/// \param hand The hand.
/// \return A random unknown color in the hand, or -1 if all colors are known.
color_t random_unknown_color(const hand_t *hand);

/// Gets the number of cards in the hand with the given color.
/// \param hand The hand.
/// \param color The color.
/// \return The number of cards in the hand with the given color.
int cards_with_color(const hand_t *hand, color_t color);

/// Gets the number of cards in the hand with the given number.
/// \param hand The hand.
/// \param number The number.
/// \return The number of cards in the hand with the given number.
int cards_with_number(const hand_t *hand, int number);

/// Gets the index of the card in the hand with the given number.
/// \param hand The hand.
/// \param number The number.
/// \return The success status.
int give_number_clue(const hand_t *from, hand_t *to, int number);

/// Gets the index of the card in the hand with the given color.
/// \param hand The hand.
/// \param color The color.
/// \return The success status.
int give_color_clue(const hand_t *from, hand_t *to, color_t color);

cJSON *get_hand_json(const hand_t *hand);

hand_t load_hand(cJSON *hand_json);

#endif //HAND_H
