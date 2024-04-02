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
    card_vec_t cards;
    int discard_deck[NUMBERS][COLORS];
    int fireworks[COLORS];
} deck_t;

/// Creates a new deck. The deck is ordered.
/// \return The deck.
deck_t new_deck();

/// Frees the deck.
/// \param deck The deck.
void free_deck(deck_t *deck);

/// Shuffles the deck.
/// \param deck The deck.
/// \param iterations The number of iterations to shuffle the deck.
void shuffle_deck(deck_t *deck, uint32_t iterations);

/// Draws a card from the deck.
/// \param deck The deck.
/// \return The card drawn from the deck. If the deck is empty, returns an empty optional.
optional_card_t draw_card(deck_t *deck);

/// Returns the number of cards in the deck.
/// \param deck The deck.
/// \return The number of cards in the deck.
size_t deck_len(const deck_t *deck);

/// Returns the current score of the deck.
/// \param deck The deck.
/// \return The current score of the deck.
int get_score(const deck_t *deck);

/// Returns the lowest table.
/// \param deck The deck.
/// \return The lowest table.
int get_lowest_table(const deck_t *deck);

/// Returns whether the deck is a table (all fireworks are at 5).
/// \param deck The deck.
/// \return Whether the deck is a table.
bool is_table(const deck_t *deck);

/// Plays a card from the hand.
/// \param deck The deck.
/// \param hand The hand.
/// \param idx The index of the card to play.
/// \return Whether the operation was successful.
int play_card(deck_t *deck, hand_t *hand, uint32_t idx);

/// Discards a card from the hand.
/// \param deck The deck.
/// \param hand The hand.
/// \param idx The index of the card to discard.
void discard_card(deck_t *deck, hand_t *hand, uint32_t idx);

/// Returns whether a card is playable.
/// \param deck The deck.
/// \param card The card.
/// \return Whether the card is playable.
bool is_playable(const deck_t *deck, const card_t *card);

/// Returns a JSON object representing a deck.
/// \param deck The deck.
/// \return The JSON object.
cJSON *get_deck_json(const deck_t *deck);

/// Loads a deck from a JSON object.
/// \param deck_json The JSON object.
/// \return The deck.
deck_t load_deck(const cJSON *deck_json);

#endif //DECK_H
